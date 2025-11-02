# from .parameter import *
# from .leg import *
import maestro
servo = maestro.Controller('/dev/ttyAMA0')
from parameter import *
from leg import *
import time
from gyroscope import *
from queue import Queue


class Spider():
    def __init__(self):
        self.leg = { # leg, direction, time
            0: [Leg(0), None, 0], 
            1: [Leg(1), None, 0], 
            2: [Leg(2), None, 0], 
            3: [Leg(3), None, 0],
            4: [Leg(4), None, 0], 
            5: [Leg(5), None, 0] 
        }
        self.gait = gait[0]
        self.move_queue = Queue() # direction 
        self.step_queue = {
            0 : Queue(),
            1 : Queue(),
            2 : Queue(),
            3 : Queue(),
            4 : Queue(),
            5 : Queue()
        }
        self.error = {
            'roll': 0,
            'pitch': 0,
            'yaw': 0
        }
        self.error_sum = {
            'roll': 0,
            'pitch': 0,
            'yaw': 0
        }
        self.curr_move = None
        self.main_time = 0
        try:
            MPU_Init()
        except Exception as e:
            print(f"Error encounter: {e}")

    def add_move(self, direction_):
        self.move_queue.put(direction[direction_])

    def update_imu(self, Ax, Ay, Az, Gx, Gy, Gz):
        # roll
        roll_max_I = pid["roll"]["max_I"]
        roll_filter_coe = pid["roll"]["filter_coe"]
        roll_kp = pid["roll"]["kp"]
        roll_ki = pid["roll"]["ki"]

        roll_acc  = atan2(Ay, sqrt(Ax**2 + Az**2)) * 180 / pi
        roll  = roll_filter_coe * (roll + Gy * dt) + (1 - roll_filter_coe) * roll_acc
        error_y = 0 - roll
        self.error_sum['roll'] = max(min(-roll_max_I, self.error_sum['roll'] + error_y * dt), roll_max_I)
        self.error['roll'] = roll_kp * error_y + roll_ki * self.error_sum['roll']       

        # pitch
        pitch_max_I = pid["pitch"]["max_I"]
        pitch_filter_coe = pid["pitch"]["filter_coe"]
        pitch_kp = pid["pitch"]["kp"]
        pitch_ki = pid["pitch"]["ki"]

        pitch_acc = atan2(Ax, sqrt(Ay**2 + Az**2)) * 180 / pi
        pitch = pitch_filter_coe * (pitch + Gx * dt) + (1 - pitch_filter_coe) * pitch_acc
        error_x = 0 - pitch 
        self.error_sum['pitch'] = max(min(-pitch_max_I, self.error_sum['pitch'] + error_x * dt), pitch_max_I)
        self.error['pitch'] = - (pitch_kp * error_x + pitch_ki * self.error_sum['pitch'])


    def stop(self):
        while not self.move_queue.empty():
            try: self.move_queue.get_nowait()
            except: break

    def walk(self): # one cycle took 5ms at most to calculate
        if not self.curr_move: 
            if not self.move_queue.empty(): 
                if self.main_time == 0 or self.main_time == period/2:
                    self.curr_move = self.move_queue.get()
                    self.main_time = 0
            else: self.curr_move = None

        phase_offsets = [k * period for k in gait_params[self.gait]["phase_offsets"]]
        stop_time = gait_params[self.gait]["stop_time"]
        phase_count = sampling + stop_time * 2
        step = period / phase_count 
        time_on_air = gait_params[self.gait]["time_on_air"] * sampling * step
        time_on_ground = (time_on_air + stop_time * step, period - stop_time * step)

        for i in self.leg:
            if self.leg[i][1] == None:
                if self.curr_move:
                    if i in (0,4,5): self.leg[i][1] = [self.curr_move[0], -self.curr_move[1]]
                    else: self.leg[i][1] = self.curr_move    
            
            if self.leg[i][1]:
                direction_ = self.leg[i][1]
                phase_time = self.leg[i][2]
                if len(direction_) == 3: rotate = True
                else: rotate = False

                if self.main_time >= phase_offsets[i] or phase_time > 0:
                    leg_step = None
                    if phase_time <= time_on_air:
                        phase = (phase_time * 180)/ time_on_air
                        leg_step = self.leg[i][0].calculateWalk(phase, direction_, walk_distance, self.error['pitch'], self.error['roll'], rotate)
                    elif phase_time < time_on_ground[1] or phase_time >= time_on_ground[0]:
                        phase = 180 + ((phase_time - time_on_air) * 180)/ (time_on_ground[1] - time_on_ground[0])
                        if phase <= 360:
                            leg_step = self.leg[i][0].calculateWalk(phase, direction_, walk_distance, self.error['pitch'], self.error['roll'], rotate)
                    if not leg_step: leg_step = self.leg[i][0].curr_angle()
                    servos = spider_servo[i]
                    lst = []
                    for k in range(3): lst.append([servos[k], leg_step[k]])
                    self.step_queue[i].put(lst)
                if phase_time == 0:
                    if self.main_time >= phase_offsets[i] and self.curr_move:
                        self.leg[i][2] += step
                else:
                    self.leg[i][2] += step
                if self.leg[i][2] >= period:
                    self.leg[i][1] = None
                    self.leg[i][2] = 0
            else:
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

    def runleg(self, servos):
        for i in servos:
            servo.setTarget(i[0], i[1])

# s = Spider()
# s.add_move('w')
# s.add_move('w')
# s.add_move('w')
# for i in range(20):
#     print(f"time: {s.main_time}, direction: {s.curr_move}")
#     s.walk()
#     dct = s.step()
#     print(f"time: {s.main_time}, direction: {s.curr_move}")
#     # for leg, servos in dct.items():
#         # print(f"leg: {leg}, target: {servos}")
#         # s.runleg(servos)
#     for leg, config in s.leg.items():
#         print(f"leg: {leg}, dir: {config[1]}, time, {config[2]}")
#     print("\n")
    
