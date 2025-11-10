from .parameter import *
from .leg import *
# import maestro
# servo = maestro.Controller('/dev/ttyAMA0')
# from parameter import *
# from leg import *
# import time
# from gyroscope import *
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
        self.angle = {'roll': 0, 'pitch': 0, 'yaw': 0}
        self.error = {'roll': 0, 'pitch': 0, 'yaw': 0}
        self.error_sum = {'roll': 0, 'pitch': 0, 'yaw': 0}
        self.bias_sample = {'Ax': 0, 'Ay': 0, 'Az': 0, 'Gx': 0, 'Gy': 0, 'Gz': 0, 'count': 0}
        self.curr_move = None
        self.main_time = 0
        self.dt = 0
        self.pid = dict()
        # try:
        #     MPU_Init()
        # except Exception as e:
        #     print(f"Error encounter: {e}")

    def add_move(self, direction_):
        self.move_queue.put(direction[direction_])

    def stand(self):
        res = []
        l = 4
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
        Ax = ax - self.pid['bias']['Ax']
        Ay = ay - self.pid['bias']['Ay']
        Az = az - self.pid['bias']['Az']
        Gx = gx - self.pid['bias']['Gx'] # roll
        Gy = gy - self.pid['bias']['Gy'] # pitch
        Gz = gz - self.pid['bias']['Gz'] # yaw

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
                    if len(self.curr_move) < 3:
                        if i in (0,4,5): self.leg[i][1] = [self.curr_move[0], -self.curr_move[1]]
                        else: self.leg[i][1] = self.curr_move    
                    else: self.leg[i][1] = self.curr_move    
            
            if self.leg[i][1]:
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
                        phase = (phase_time * 180)/ time_on_air
                        leg_step = self.leg[i][0].calculateWalk(phase, direction_, walk_distance, self.error['pitch'], self.error['roll'], yaw, rotate)
                    elif phase_time < time_on_ground[1] or phase_time >= time_on_ground[0]:
                        phase = 180 + ((phase_time - time_on_air) * 180)/ (time_on_ground[1] - time_on_ground[0])
                        if phase <= 360:
                            leg_step = self.leg[i][0].calculateWalk(phase, direction_, walk_distance, self.error['pitch'], self.error['roll'], yaw, rotate)
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

    # def runleg(self, servos):
    #     for i in servos:
    #         servo.setTarget(i[0], i[1])

# s = Spider()
# while True:
#     ax,ay,az,gx,gy,gz = get_gyro()
#     s.update_imu(ax,ay,az,gx,gy,gz)
#     time.sleep(0.5)
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
    
