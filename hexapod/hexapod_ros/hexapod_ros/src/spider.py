from .parameter import *
from .leg import *
from queue import Queue

class Spider():
    """
    Main controller for the Hexapod. Handles movement queues, 
    IMU data processing, and gait sequencing.
    """
    def __init__(self):
        # Dictionary mapping leg ID to [Leg Object, Current Direction, Current Time in Cycle]
        self.leg = {
            0: [Leg(0), None, 0], 
            1: [Leg(1), None, 0], 
            2: [Leg(2), None, 0], 
            3: [Leg(3), None, 0],
            4: [Leg(4), None, 0], 
            5: [Leg(5), None, 0] 
        }
        self.gait = gait[0]  # Default to "tripod" gait
        self.move_queue = Queue() 
        self.step_queue = {i: Queue() for i in range(6)} # Buffer for scheduled servo positions
        
        # Orientation state
        self.angle = {'roll': 0, 'pitch': 0, 'yaw': 0}
        self.error = {'roll': 0, 'pitch': 0, 'yaw': 0}      # Current PID output
        self.error_sum = {'roll': 0, 'pitch': 0, 'yaw': 0}  # Integral term for PID
        self.bias_sample = {'Ax': 0, 'Ay': 0, 'Az': 0, 'Gx': 0, 'Gy': 0, 'Gz': 0, 'count': 0}
        
        self.curr_move = None
        self.main_time = 0  # Global clock for the gait cycle
        self.dt = 0.002     # Delta time for PID calculations
        self.pid = dict()   # Should be populated with Kp, Ki, Kd values

    def add_move(self, direction_):
        """Adds a movement command (e.g., 'w', 'a', 's', 'd') to the queue."""
        self.move_queue.put(direction[direction_])

    def stand(self):
        """Generates a sequence of frames to move the robot into a standing position (brute-force)."""
        res = []
        l = 4 # Number of steps in the standing animation
        for i in range(l):
            for leg in self.leg:
                servos = spider_servo[leg]
                lst = []
                curr = self.leg[leg][0].stand(l, i)
                for j in range(3):
                    lst.append([servos[j], curr[j]])
                res.append(lst)
        return res
    
    def calibrate_imu(self, ax, ay, az, gx, gy, gz):
        """Averages IMU readings over a sample count to find the zero-bias."""
        if self.bias_sample['count'] < self.pid['bias']['count']:
            # Accumulate samples
            self.bias_sample['Ax'] += ax
            self.bias_sample['Ay'] += ay
            self.bias_sample['Az'] += az
            self.bias_sample['Gx'] += gx
            self.bias_sample['Gy'] += gy
            self.bias_sample['Gz'] += gz
            self.bias_sample['count'] += 1
            return False
        elif self.bias_sample['count'] == self.pid['bias']['count']:
            # Calculate mean and set initial roll/pitch based on gravity vector
            self.pid['bias']['Ax'] = self.bias_sample['Ax']/self.bias_sample['count']
            self.pid['bias']['Ay'] = self.bias_sample['Ay']/self.bias_sample['count']
            self.pid['bias']['Az'] = self.bias_sample['Az']/self.bias_sample['count'] + g
            self.pid['bias']['Gx'] = self.bias_sample['Gx']/self.bias_sample['count']
            self.pid['bias']['Gy'] = self.bias_sample['Gy']/self.bias_sample['count'] 
            self.pid['bias']['Gz'] = self.bias_sample['Gz']/self.bias_sample['count']
            self.pid['bias']['roll']  = atan2(self.pid['bias']['Ay'], sqrt(self.pid['bias']['Ax']**2 + (self.pid['bias']['Az']-g)**2)) * 180 / pi
            self.pid['bias']['pitch']  = atan2(self.pid['bias']['Ax'], sqrt(self.pid['bias']['Ay']**2 + (self.pid['bias']['Az']-g)**2)) * 180 / pi
            self.pid['bias']['calibrated'] = 1
            return True

    def update_imu(self, ax, ay, az, gx, gy, gz): 
        """
        Uses a Complementary Filter to combine Gyro (fast) and Accel (stable) 
        data, then runs a PID loop to calculate the correction angle.
        """
        # Subtract calibrated bias
        Ax, Ay, Az = ax - self.pid['bias']['Ax'], ay - self.pid['bias']['Ay'], az - self.pid['bias']['Az']
        Gx, Gy, Gz = gx - self.pid['bias']['Gx'], gy - self.pid['bias']['Gy'], gz - self.pid['bias']['Gz']

        # roll
        roll_max_I = self.pid["roll"]["max_I"]
        roll_max_angle = self.pid["roll"]["max_angle"]
        roll_filter_coe = self.pid["roll"]["filter_coe"]
        roll_kp = self.pid["roll"]["kp"]
        roll_ki = self.pid["roll"]["ki"]
        roll_kd = self.pid["roll"]["kd"]
        prev_roll = self.angle['roll']
        roll_acc  = atan2(Ay, sqrt(Ax**2 + Az**2)) * 180 / pi
        self.angle['roll'] = roll_filter_coe * (prev_roll + Gx * self.dt) + (1 - roll_filter_coe) * roll_acc
        error_x = self.pid['bias']['roll'] - self.angle['roll']
        self.error_sum['roll'] = min(max(-roll_max_I, self.error_sum['roll'] + error_x * self.dt), roll_max_I)
        self.error['roll'] = min(max(-roll_max_angle, roll_kp * error_x + roll_ki * self.error_sum['roll'] + roll_kd * (error_x - (self.pid['bias']['roll'] - prev_roll))/self.dt), roll_max_angle)

        # pitch
        pitch_max_I = self.pid["pitch"]["max_I"]
        pitch_max_angle = self.pid["pitch"]["max_angle"]
        pitch_filter_coe = self.pid["pitch"]["filter_coe"]
        pitch_kp = self.pid["pitch"]["kp"]
        pitch_ki = self.pid["pitch"]["ki"]
        pitch_kd = self.pid["pitch"]["kd"]
        prev_pitch = self.angle['pitch']
        pitch_acc = atan2(Ax, sqrt(Ay**2 + Az**2)) * 180 / pi
        self.angle['pitch'] = pitch_filter_coe * (prev_pitch + Gy * self.dt) + (1 - pitch_filter_coe) * pitch_acc
        error_y = self.pid['bias']['pitch'] - self.angle['pitch']
        self.error_sum['pitch'] = min(max(-pitch_max_I, self.error_sum['pitch'] + error_y * self.dt), pitch_max_I)
        self.error['pitch'] = -min(max(-pitch_max_angle, pitch_kp * error_y + pitch_ki * self.error_sum['pitch'] + pitch_kd * (error_y - (self.pid['bias']['pitch'] - prev_pitch))/self.dt), pitch_max_angle)

        # yaw
        yaw_max_I = self.pid["yaw"]["max_I"]
        yaw_max_angle = self.pid["yaw"]["max_angle"]
        yaw_kp = self.pid["yaw"]["kp"]
        yaw_ki = self.pid["yaw"]["ki"]
        yaw_kd = self.pid["yaw"]["kd"]
        prev_yaw = self.angle['yaw']
        self.angle['yaw'] = prev_yaw + Gz * self.dt
        error_y = 0 - self.angle['yaw']
        self.error_sum['yaw'] = min(max(yaw_max_I, self.error_sum['yaw'] + error_y * self.dt), yaw_max_I)
        self.error['yaw'] = -min(max(-yaw_max_angle, yaw_kp * error_y + yaw_ki * self.error_sum['yaw'] + yaw_kd * (error_y - (0 - prev_yaw))/self.dt), yaw_max_angle)

    def stop(self):
        while not self.move_queue.empty():
            try: self.move_queue.get_nowait()
            except: break

    def walk(self):
        """
        The 'Brain' of the walking movement. 
        Calculates where each leg should be based on the current Gait and Time.
        """
        if not self.curr_move: 
            if not self.move_queue.empty(): 
                # Synchronize move start with gait cycle phase
                if self.main_time == 0 or self.main_time == period/2:
                    self.curr_move = self.move_queue.get()
                    self.main_time = 0
            else: self.curr_move = None

        # Gait timing parameters
        phase_offsets = [k * period for k in gait_params[self.gait]["phase_offsets"]]
        stop_time = gait_params[self.gait]["stop_time"]
        phase_count = sampling + stop_time * 2
        step = period / phase_count 
        time_on_air = gait_params[self.gait]["time_on_air"] * sampling * step
        time_on_ground = (time_on_air + stop_time * step, period - stop_time * step)

        for i in self.leg:
            # Determine leg direction (mirroring for opposite side of body)
            if self.leg[i][1] == None:
                if self.curr_move:
                    if len(self.curr_move) < 3:
                        if i in (0,4,5): self.leg[i][1] = [self.curr_move[0], -self.curr_move[1]]
                        else: self.leg[i][1] = self.curr_move    
                    else: self.leg[i][1] = self.curr_move    
            
            if self.leg[i][1]:
                # Leg is moving: Calculate Swing (Air) vs Stance (Ground)
                direction_ = self.leg[i][1]
                phase_time = self.leg[i][2]
                yaw = self.error['yaw']
                if len(direction_) == 3: 
                    rotate = True
                    yaw = 0
                else: rotate = False

                if self.main_time >= phase_offsets[i] or phase_time > 0:
                    leg_step = None
                    if phase_time <= time_on_air:
                        # Swing Phase: Lift leg and move forward
                        phase = (phase_time * 180)/ time_on_air
                        leg_step = self.leg[i][0].calculateWalk(phase, direction_, walk_distance, self.error['pitch'], self.error['roll'], yaw, rotate)
                    elif phase_time < time_on_ground[1] or phase_time >= time_on_ground[0]:
                        # Stance Phase: Push against ground to move body
                        phase = 180 + ((phase_time - time_on_air) * 180)/ (time_on_ground[1] - time_on_ground[0])
                        if phase <= 360:
                            leg_step = self.leg[i][0].calculateWalk(phase, direction_, walk_distance, self.error['pitch'], self.error['roll'], yaw, rotate)
                    if not leg_step: leg_step = self.leg[i][0].curr_angle()
                    # Queue the servo commands
                    servos = spider_servo[i]
                    lst = []
                    for k in range(3): lst.append([servos[k], leg_step[k]])
                    self.step_queue[i].put(lst)

                # Increment leg internal clock
                if phase_time == 0:
                    if self.main_time >= phase_offsets[i] and self.curr_move:
                        self.leg[i][2] += step
                else:
                    self.leg[i][2] += step
                if self.leg[i][2] >= period:
                    self.leg[i][1] = None
                    self.leg[i][2] = 0
            else:
                # Leg is stationary: Apply self-balancing only
                leg_step = self.leg[i][0].balance(self.error['pitch'], self.error['roll'])
                servos = spider_servo[i]
                lst = []
                for k in range(3): lst.append([servos[k], leg_step[k]])
                self.step_queue[i].put(lst)

        self.main_time += step
        if self.main_time >= period:
            self.curr_move = None
            self.main_time = 0

    def step(self):
        """ Return each queue step of the leg to node"""
        action = dict()
        for leg in self.leg:
            if not self.step_queue[leg].empty():
                action[leg] = self.step_queue[leg].get()
            else:
                servos = spider_servo[leg]
                lst = []
                curr = self.leg[leg][0].curr_angle()
                for i in range(3):
                    lst.append([servos[i], curr[i]])
                action[leg] = lst
        return action

    def gaitChange(self, inp):
        self.gait = gait[inp]

   
