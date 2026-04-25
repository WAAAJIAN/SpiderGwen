## spider.py
## RPi-side gait engine for SpiderGwen hexapod.
##
## Responsibilities:
##   - Maintains move queue and gait phase state for all 6 legs
##   - Calls legstate.py trajectory functions to compute foot (x, y, z) each tick
##   - Runs IMU complementary filter + PID for balance corrections
##   - Outputs {leg_id: (x, y, z)} via step(), which hexapod_controller.py
##     forwards to the ESP32 over UART
##
## What this file does NOT do:
##   - IK / servo angle computation  →  ESP32 leg_kinematics.cpp
##   - Servo execution               →  ESP32 spider.cpp
##   - Stand sequence                →  ESP32 Spider::stand()
##   - UART communication            →  esp32_interface.py

from math import atan2, sqrt, pi
from queue import Queue
from .leg_state import LegState, calculate_walk_xyz, calculate_balance_xyz
from .parameter import (
    gait, gait_params,
    period, sampling,
    walk_distance,
    direction,
    g
)


class Spider:
    """
    Gait engine and IMU controller for the hexapod RPi side.
    Computes desired foot positions and exposes them via step().
    """

    def __init__(self):
        # Per-leg state: LegState object, current move direction, phase time in cycle
        self.leg = {
            i: {
                'state':      LegState(i),
                'direction':  None,
                'phase_time': 0
            }
            for i in range(6)
        }

        self.gait       = gait[0]                          # Default: tripod
        self.move_queue = Queue()
        self.step_queue = {i: Queue() for i in range(6)}   # Per-leg output buffer

        # IMU / orientation state
        self.angle     = {'roll': 0, 'pitch': 0, 'yaw': 0}
        self.error     = {'roll': 0, 'pitch': 0, 'yaw': 0}       # PID output
        self.error_sum = {'roll': 0, 'pitch': 0, 'yaw': 0}       # PID integral
        self.bias_sample = {
            'Ax': 0, 'Ay': 0, 'Az': 0,
            'Gx': 0, 'Gy': 0, 'Gz': 0,
            'count': 0
        }

        self.curr_move = None
        self.main_time = 0       # Global gait clock
        self.dt        = 0.002   # Control loop delta time (seconds)
        self.pid       = dict()  # Populated by hexapod_controller via load_pid()

    # ------------------------------------------------------------------ #
    #  Movement queue
    # ------------------------------------------------------------------ #

    def add_move(self, direction_: str):
        """Queue a movement command key: 'w', 'a', 's', 'd', 'q', 'e', 'z', 'x', 'o', 'p'"""
        self.move_queue.put(direction[direction_])

    def stop(self):
        """Flush the movement queue and clear current move."""
        while not self.move_queue.empty():
            try:
                self.move_queue.get_nowait()
            except Exception:
                break
        self.curr_move = None

    # ------------------------------------------------------------------ #
    #  IMU calibration
    # ------------------------------------------------------------------ #

    def calibrate_imu(self, ax, ay, az, gx, gy, gz) -> bool:
        """
        Accumulates IMU samples to compute zero-bias offsets.
        Returns True when calibration is complete.
        """
        if self.bias_sample['count'] < self.pid['bias']['count']:
            self.bias_sample['Ax'] += ax
            self.bias_sample['Ay'] += ay
            self.bias_sample['Az'] += az
            self.bias_sample['Gx'] += gx
            self.bias_sample['Gy'] += gy
            self.bias_sample['Gz'] += gz
            self.bias_sample['count'] += 1
            return False

        elif self.bias_sample['count'] == self.pid['bias']['count']:
            n = self.bias_sample['count']
            self.pid['bias']['Ax']  = self.bias_sample['Ax'] / n
            self.pid['bias']['Ay']  = self.bias_sample['Ay'] / n
            self.pid['bias']['Az']  = self.bias_sample['Az'] / n + g
            self.pid['bias']['Gx']  = self.bias_sample['Gx'] / n
            self.pid['bias']['Gy']  = self.bias_sample['Gy'] / n
            self.pid['bias']['Gz']  = self.bias_sample['Gz'] / n
            self.pid['bias']['roll']  = atan2(
                self.pid['bias']['Ay'],
                sqrt(self.pid['bias']['Ax']**2 + (self.pid['bias']['Az'] - g)**2)
            ) * 180 / pi
            self.pid['bias']['pitch'] = atan2(
                self.pid['bias']['Ax'],
                sqrt(self.pid['bias']['Ay']**2 + (self.pid['bias']['Az'] - g)**2)
            ) * 180 / pi
            self.pid['bias']['calibrated'] = 1
            return True

    # ------------------------------------------------------------------ #
    #  IMU complementary filter + PID
    # ------------------------------------------------------------------ #

    def update_imu(self, ax, ay, az, gx, gy, gz):
        """
        Complementary filter combines gyro (fast, drifts) and accelerometer
        (slow, stable) to estimate roll/pitch/yaw. PID converts the angle
        error into a correction value used by the balance trajectory math.
        """
        Ax = ax - self.pid['bias']['Ax']
        Ay = ay - self.pid['bias']['Ay']
        Az = az - self.pid['bias']['Az']
        Gx = gx - self.pid['bias']['Gx']
        Gy = gy - self.pid['bias']['Gy']
        Gz = gz - self.pid['bias']['Gz']

        # --- Roll ---
        roll_max_I      = self.pid["roll"]["max_I"]
        roll_max_angle  = self.pid["roll"]["max_angle"]
        roll_filter_coe = self.pid["roll"]["filter_coe"]
        roll_kp         = self.pid["roll"]["kp"]
        roll_ki         = self.pid["roll"]["ki"]
        roll_kd         = self.pid["roll"]["kd"]

        prev_roll          = self.angle['roll']
        roll_acc           = atan2(Ay, sqrt(Ax**2 + Az**2)) * 180 / pi
        self.angle['roll'] = (roll_filter_coe * (prev_roll + Gx * self.dt)
                              + (1 - roll_filter_coe) * roll_acc)
        err_roll = self.pid['bias']['roll'] - self.angle['roll']
        self.error_sum['roll'] = min(max(-roll_max_I,
                                        self.error_sum['roll'] + err_roll * self.dt),
                                     roll_max_I)
        self.error['roll'] = min(max(-roll_max_angle,
                                     roll_kp * err_roll
                                     + roll_ki * self.error_sum['roll']
                                     + roll_kd * (err_roll - (self.pid['bias']['roll'] - prev_roll)) / self.dt),
                                 roll_max_angle)

        # --- Pitch ---
        pitch_max_I      = self.pid["pitch"]["max_I"]
        pitch_max_angle  = self.pid["pitch"]["max_angle"]
        pitch_filter_coe = self.pid["pitch"]["filter_coe"]
        pitch_kp         = self.pid["pitch"]["kp"]
        pitch_ki         = self.pid["pitch"]["ki"]
        pitch_kd         = self.pid["pitch"]["kd"]

        prev_pitch          = self.angle['pitch']
        pitch_acc           = atan2(Ax, sqrt(Ay**2 + Az**2)) * 180 / pi
        self.angle['pitch'] = (pitch_filter_coe * (prev_pitch + Gy * self.dt)
                               + (1 - pitch_filter_coe) * pitch_acc)
        err_pitch = self.pid['bias']['pitch'] - self.angle['pitch']
        self.error_sum['pitch'] = min(max(-pitch_max_I,
                                         self.error_sum['pitch'] + err_pitch * self.dt),
                                      pitch_max_I)
        self.error['pitch'] = -min(max(-pitch_max_angle,
                                       pitch_kp * err_pitch
                                       + pitch_ki * self.error_sum['pitch']
                                       + pitch_kd * (err_pitch - (self.pid['bias']['pitch'] - prev_pitch)) / self.dt),
                                   pitch_max_angle)

        # --- Yaw ---
        yaw_max_I     = self.pid["yaw"]["max_I"]
        yaw_max_angle = self.pid["yaw"]["max_angle"]
        yaw_kp        = self.pid["yaw"]["kp"]
        yaw_ki        = self.pid["yaw"]["ki"]
        yaw_kd        = self.pid["yaw"]["kd"]

        prev_yaw          = self.angle['yaw']
        self.angle['yaw'] = prev_yaw + Gz * self.dt
        err_yaw = 0 - self.angle['yaw']
        self.error_sum['yaw'] = min(max(yaw_max_I,
                                        self.error_sum['yaw'] + err_yaw * self.dt),
                                    yaw_max_I)
        self.error['yaw'] = -min(max(-yaw_max_angle,
                                      yaw_kp * err_yaw
                                      + yaw_ki * self.error_sum['yaw']
                                      + yaw_kd * (err_yaw - (0 - prev_yaw)) / self.dt),
                                 yaw_max_angle)

    # ------------------------------------------------------------------ #
    #  Gait engine
    # ------------------------------------------------------------------ #

    def walk(self):
        """
        Advances the gait state machine by one tick.
        Computes target (x, y, z) for each leg and pushes to step_queue.
        Called every control loop tick (50 Hz) by hexapod_controller.
        """
        # Consume next move at a clean cycle boundary
        if not self.curr_move:
            if not self.move_queue.empty():
                if self.main_time == 0 or self.main_time == period / 2:
                    self.curr_move = self.move_queue.get()
                    self.main_time = 0
            else:
                self.curr_move = None

        # Gait timing parameters
        phase_offsets  = [k * period for k in gait_params[self.gait]["phase_offsets"]]
        stop_time      = gait_params[self.gait].get("stop_time", 0)
        phase_count    = sampling + stop_time * 2
        step           = period / phase_count
        time_on_air    = gait_params[self.gait]["time_on_air"] * sampling * step
        time_on_ground = (
            time_on_air + stop_time * step,
            period - stop_time * step
        )

        for i in self.leg:
            leg   = self.leg[i]
            state = leg['state']

            # Assign direction to leg when it becomes active
            if leg['direction'] is None and self.curr_move:
                if len(self.curr_move) < 3:
                    # Translational move: mirror X for legs on the left side of body
                    if i in (0, 4, 5):
                        leg['direction'] = [self.curr_move[0], -self.curr_move[1]]
                    else:
                        leg['direction'] = self.curr_move
                else:
                    # Rotational move: same vector for all legs
                    leg['direction'] = self.curr_move

            if leg['direction']:
                direction_  = leg['direction']
                phase_time  = leg['phase_time']
                yaw         = self.error['yaw']
                rotate      = len(direction_) == 3
                if rotate:
                    yaw = 0  # Yaw PID not applied during intentional rotation

                foot_xyz = None

                if self.main_time >= phase_offsets[i] or phase_time > 0:

                    if phase_time <= time_on_air:
                        # Swing phase: foot lifts and steps forward
                        phase    = (phase_time * 180) / time_on_air
                        foot_xyz = calculate_walk_xyz(
                            state, phase, direction_, walk_distance,
                            self.error['pitch'], self.error['roll'], yaw, rotate
                        )
                    elif (phase_time < time_on_ground[1]
                          or phase_time >= time_on_ground[0]):
                        # Stance phase: foot on ground, body driven forward
                        phase = 180 + ((phase_time - time_on_air) * 180) / (
                            time_on_ground[1] - time_on_ground[0])
                        if phase <= 360:
                            foot_xyz = calculate_walk_xyz(
                                state, phase, direction_, walk_distance,
                                self.error['pitch'], self.error['roll'], yaw, rotate
                            )

                    if foot_xyz is None:
                        foot_xyz = state.get_position()   # Hold current position
                    else:
                        state.set_position(*foot_xyz)     # Update tracked state

                    self.step_queue[i].put(foot_xyz)

                # Advance this leg's phase clock
                if phase_time == 0:
                    if self.main_time >= phase_offsets[i] and self.curr_move:
                        leg['phase_time'] += step
                else:
                    leg['phase_time'] += step

                # End of cycle: reset leg
                if leg['phase_time'] >= period:
                    leg['direction']  = None
                    leg['phase_time'] = 0

            else:
                # Leg is stationary: apply balance correction only
                foot_xyz = calculate_balance_xyz(
                    state, self.error['pitch'], self.error['roll']
                )
                state.set_position(*foot_xyz)
                self.step_queue[i].put(foot_xyz)

        # Advance global gait clock
        self.main_time += step
        if self.main_time >= period:
            self.curr_move = None
            self.main_time = 0

    # ------------------------------------------------------------------ #
    #  Output
    # ------------------------------------------------------------------ #

    def step(self) -> dict:
        """
        Returns the next foot position for each leg as {leg_id: (x, y, z)}.
        If a leg's queue is empty (e.g. before first walk() call),
        returns its current tracked position as a safe fallback.
        """
        positions = {}
        for i in self.leg:
            if not self.step_queue[i].empty():
                positions[i] = self.step_queue[i].get()
            else:
                positions[i] = self.leg[i]['state'].get_position()
        return positions

    # ------------------------------------------------------------------ #
    #  Gait selection
    # ------------------------------------------------------------------ #

    def gait_change(self, inp: int):
        """Switch gait pattern. inp: 0=tripod, 1=wave, 2=ripple, 3=bipod, 4=tetra"""
        self.gait = gait[inp]