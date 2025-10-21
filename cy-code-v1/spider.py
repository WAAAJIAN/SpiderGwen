from parameter import *
from leg import *
from gyroscope import *

class Spider:
    def __init__(self):
        self.leg = {
            #  0: Leg(0, 6, 23, 12), 
            #  5: Leg(5, 7, 22, 13), 
            #  4: Leg(4, 8, 21, 14), 
            # 1: Leg(1, 11, 18, 17), 
            2: Leg(2, 10, 19, 16), 
            # 3: Leg(3, 9, 20, 15)
        }
        '''
            0 (0,0)   1 (1,0)
             \     /
              \   /
    5 (0,1)- - - - - - - 2 (1,1)
              /   \ 
             /     \ 
            4 (0,2)   3 (1,2)
        '''
        self.time = 0
        self.gait = gait[0]
        self.runleg()
        try:
            MPU_Init()
        except Exception as e:
            print(f"Error encounter: {e}")

    def balance(self):
        roll, pitch = 0,0
        error_sum_x, error_sum_y = 0, 0

        roll_max_I = pid["roll"]["max_I"]
        pitch_max_I = pid["pitch"]["max_I"]

        roll_filter_coe = pid["roll"]["filter_coe"]
        pitch_filter_coe = pid["pitch"]["filter_coe"]
        
        roll_kp = pid["roll"]["kp"]
        pitch_kp = pid["pitch"]["kp"]

        roll_ki = pid["roll"]["ki"]
        pitch_ki = pid["pitch"]["ki"]

        while True:
            ax,ay,az,gx,gy,gz = get_gyro()

            roll_acc  = atan2(ay, sqrt(ax**2 + az**2)) * 180 / pi
            pitch_acc = atan2(ax, sqrt(ay**2 + az**2)) * 180 / pi

            roll  = roll_filter_coe * (roll + gy * dt) + (1 - roll_filter_coe) * roll_acc
            pitch = pitch_filter_coe * (pitch + gx * dt) + (1 - pitch_filter_coe) * pitch_acc

            error_x = 0 - pitch 
            error_y = 0 - roll
            
            error_sum_x += error_x * dt
            error_sum_y += error_y * dt

            if error_sum_x > pitch_max_I: error_sum_x = pitch_max_I
            elif error_sum_x < -pitch_max_I: error_sum_x = -pitch_max_I
            if error_sum_y > roll_max_I: error_sum_y = roll_max_I
            elif error_sum_y < -roll_max_I: error_sum_y = -roll_max_I

            correction_x = - (pitch_kp * error_x + pitch_ki * error_sum_x)
            correction_y = roll_kp * error_y + roll_ki * error_sum_y
            # correction =  kp*error_x + ki*error_sum + kd*(error_x - last_error)
            print("error sum", error_sum_x, error_sum_y)
            print("correction angle:", correction_x, correction_y,"\n")
            for i in self.leg:
                self.leg[i].rotating(correction_x, correction_y)
            self.runleg()
            sleep(dt)
        
    def stop_leg(self):
        for i in self.leg:
            self.leg[i].clean()

    def walkCycle(self, loop, direction):
        time_on_air = gait_params[self.gait]["time_on_air"] * period
        phase_offsets = gait_params[self.gait]["phase_offsets"]

        self.walk(direction, 0, time_on_air, phase_offsets)
        
        for i in range(loop):
            self.walk(direction, 1, time_on_air, phase_offsets)
        
        self.walk(direction, 2, time_on_air, phase_offsets)

    def walk(self, direction, type_, time_on_air, phase_offsets):        
        distance = 50
        while(self.time <= 2 * period - time_on_air):            
            for i in self.leg:
                if self.time >= phase_offsets[i] * period:
                    leg_time = self.time - phase_offsets[i] * period
                    if leg_time <= time_on_air:
                        phase = (leg_time * 180)/time_on_air
                        self.leg[i].calculateWalk(phase, direction, distance, type_)
                    else:
                        phase = 180 + ((leg_time - time_on_air) * 180)/(period - time_on_air)
                        if phase <= 360:
                            self.leg[i].calculateWalk(phase, direction, distance, type_)
            self.runleg()
            sleep(dt)
            self.time += steps
        self.time = 0

    # def walk(self, direction, type_, time_on_air, phase_offsets):
    #     roll, pitch = 0,0
    #     error_sum_x, error_sum_y = 0, 0

    #     roll_max_I = pid["roll"]["max_I"]
    #     pitch_max_I = pid["pitch"]["max_I"]

    #     roll_filter_coe = pid["roll"]["filter_coe"]
    #     pitch_filter_coe = pid["pitch"]["filter_coe"]
        
    #     roll_kp = pid["roll"]["kp"]
    #     pitch_kp = pid["pitch"]["kp"]

    #     roll_ki = pid["roll"]["ki"]
    #     pitch_ki = pid["pitch"]["ki"]
       
    #     distance = 35
    #     while(self.time <= 2 * period - time_on_air):
    #         ax,ay,az,gx,gy,gz = get_gyro()

    #         roll_acc  = atan2(ay, sqrt(ax**2 + az**2)) * 180 / pi
    #         pitch_acc = atan2(ax, sqrt(ay**2 + az**2)) * 180 / pi

    #         roll  = roll_filter_coe * (roll + gy * dt) + (1 - roll_filter_coe) * roll_acc
    #         pitch = pitch_filter_coe * (pitch + gx * dt) + (1 - pitch_filter_coe) * pitch_acc

    #         error_x = 0 - pitch 
    #         error_y = 0 - roll
            
    #         error_sum_x += error_x * dt
    #         error_sum_y += error_y * dt

    #         if error_sum_x > pitch_max_I: error_sum_x = pitch_max_I
    #         elif error_sum_x < -pitch_max_I: error_sum_x = -pitch_max_I
    #         if error_sum_y > roll_max_I: error_sum_y = roll_max_I
    #         elif error_sum_y < -roll_max_I: error_sum_y = -roll_max_I

    #         correction_x = - (pitch_kp * error_x + pitch_ki * error_sum_x)
    #         correction_y = roll_kp * error_y + roll_ki * error_sum_y            
            
    #         for i in self.leg:
    #             if self.time >= phase_offsets[i] * period:
    #                 leg_time = self.time - phase_offsets[i] * period
    #                 if leg_time <= time_on_air:
    #                     phase = (leg_time * 180)/time_on_air
    #                     self.leg[i].walknbalance(phase, direction, distance, type_, correction_x, correction_y)
    #                 else:
    #                     phase = 180 + ((leg_time - time_on_air) * 180)/(period - time_on_air)
    #                     self.leg[i].walknbalance(phase, direction, distance, type_, correction_x, correction_y)
    #         self.runleg()
    #         sleep(dt)
    #         self.time += steps
    #     self.time = 0

    # def waveCycle(self, direction):
    #     time_on_air = 1/6
    #     while (self.time <= (11/6) * period):
    #         if self.time <= period: self.leg[0].calculateWalk(self.time, time_on_air, direction)
    #         if self.time >= (1/6) * period and self.time <= (7/6) * period: self.leg[5].calculateWalk(self.time - (1/6) * period, time_on_air, direction)
    #         if self.time >= (2/6) * period and self.time <= (8/6) * period: self.leg[4].calculateWalk(self.time - (2/6) * period, time_on_air, direction)
    #         if self.time >= (3/6) * period and self.time <= (9/6) * period: self.leg[3].calculateWalk(self.time - (3/6) * period, time_on_air, direction)
    #         if self.time >= (4/6) * period and self.time <= (10/6) * period: self.leg[2].calculateWalk(self.time - (4/6) * period, time_on_air, direction)
    #         if self.time >= (5/6) * period and self.time <= (11/6) * period: self.leg[1].calculateWalk(self.time - (5/6) * period, time_on_air, direction)
    #         self.runleg()
    #         self.time += steps
    #     self.time = 0

    # def rippleCycle(self, direction):
    #     time_on_air = 1/6
    #     while (self.time <= (11/6) * period):
    #         if self.time <= period: self.leg[0].calculateWalk(self.time, time_on_air, direction)
    #         if self.time >= (1/6) * period and self.time <= (7/6) * period: self.leg[3].calculateWalk(self.time - (1/6) * period, time_on_air, direction)
    #         if self.time >= (2/6) * period and self.time <= (8/6) * period: self.leg[5].calculateWalk(self.time - (2/6) * period, time_on_air, direction)
    #         if self.time >= (3/6) * period and self.time <= (9/6) * period: self.leg[2].calculateWalk(self.time - (3/6) * period, time_on_air, direction)
    #         if self.time >= (4/6) * period and self.time <= (10/6) * period: self.leg[4].calculateWalk(self.time - (4/6) * period, time_on_air, direction)
    #         if self.time >= (5/6) * period and self.time <= (11/6) * period: self.leg[1].calculateWalk(self.time - (5/6) * period, time_on_air, direction)
    #         self.runleg()
    #         self.time += steps
    #     self.time = 0

    # def biCycle(self, direction):
    #     time_on_air = 1/3
    #     while (self.time <= (11/6) * period):
    #         if self.time <= period: self.leg[2].calculateWalk(self.time, time_on_air, direction)
    #         if self.time <= period: self.leg[5].calculateWalk(self.time, time_on_air, direction)
    #         if self.time >= (1/3) * period and self.time <= (4/3) * period: self.leg[4].calculateWalk(self.time - (1/3) * period, time_on_air, direction)
    #         if self.time >= (1/3) * period and self.time <= (4/3) * period: self.leg[1].calculateWalk(self.time - (1/3) * period, time_on_air, direction)
    #         if self.time >= (2/3) * period and self.time <= (5/3) * period: self.leg[0].calculateWalk(self.time - (2/3) * period, time_on_air, direction)
    #         if self.time >= (2/3) * period and self.time <= (5/3) * period: self.leg[3].calculateWalk(self.time - (2/3) * period, time_on_air, direction)
    #         self.runleg()
    #         self.time += steps
    #     self.time = 0

    # def tetraCycle(self, direction):
    #     time_on_air = 1/3
    #     while (self.time <= (11/6) * period):
    #         if self.time <= period: self.leg[0].calculateWalk(self.time, time_on_air, direction)
    #         if self.time <= period: self.leg[3].calculateWalk(self.time, time_on_air, direction)
    #         if self.time >= (1/3) * period and self.time <= (4/3) * period: self.leg[5].calculateWalk(self.time - (1/3) * period, time_on_air, direction)
    #         if self.time >= (1/3) * period and self.time <= (4/3) * period: self.leg[1].calculateWalk(self.time - (1/3) * period, time_on_air, direction)
    #         if self.time >= (2/3) * period and self.time <= (5/3) * period: self.leg[4].calculateWalk(self.time - (2/3) * period, time_on_air, direction)
    #         if self.time >= (2/3) * period and self.time <= (5/3) * period: self.leg[2].calculateWalk(self.time - (2/3) * period, time_on_air, direction)
    #         self.runleg()
    #         self.time += steps
    #     self.time = 0

    def gaitChange(self, inp):
        self.gait = gait[inp]

    def runleg(self):
        for i in self.leg:
            self.leg[i].run()
