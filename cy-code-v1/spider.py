from parameter import *
from leg import *
from gyroscope import *

class Spider:
    def __init__(self):
        #self.leg = {5: Leg(5,3,4,5)}
        #self.leg = {2 : Leg(2, 18, 19, 20)}
        # self.leg = {
        #     0: Leg(0, 0, 1, 2), 
        #     5: Leg(5, 3, 4, 5), 
        #     4: Leg(4, 6, 7, 8), 
        #     1: Leg(1, 21, 22, 23), 
        #     2: Leg(2, 18, 19, 20), 
        #     3: Leg(3, 9, 10, 11)
        # }
        self.leg = {
            0: Leg(0, 6, 23, 12), 
            5: Leg(5, 7, 22, 13), 
            4: Leg(4, 8, 21, 14), 
            1: Leg(1, 11, 18, 17), 
            2: Leg(2, 10, 19, 16), 
            3: Leg(3, 9, 20, 15)
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
        self.gaitFunction = {
            0: self.triCycle, 
            1: self.waveCycle, 
            2: self.rippleCycle, 
            3: self.biCycle, 
            4: self.tetraCycle
            }
        self.gait = 0
        self.runleg()
        try:
            MPU_Init()
        except Exception as e:
            print(f"Error encounter: {e}")

    def balance(self):
        global roll, pitch
        while True:
            ax,ay,az,gx,gy,gz = get_gyro()

            roll_acc  = atan2(ay, sqrt(ax**2 + az**2)) * 180 / pi
            pitch_acc = atan2(ax, sqrt(ay**2 + az**2)) * 180 / pi
            
            roll  = filtercoe * (roll + gy * dt) + (1 - filtercoe) * roll_acc
            pitch = filtercoe * (pitch + gx * dt) + (1 - filtercoe) * pitch_acc
            
            error_x = 0 - pitch 
            error_y = 0 - roll
            
            correction_x = -kp * error_x
            correction_y = -kp * error_y
            # correction =  kp*error_x + ki*error_sum + kd*(error_x - last_error)

            for i in self.leg:
                self.leg[i].rotating(correction_x, correction_y)
            self.runleg()
            sleep(dt)

    def rotate_x(self, angle): # roll
        for i in self.leg:
            turning_angle = angle
            if i == 0 or i == 5 or i == 4: 
                turning_angle = -turning_angle
            # print(f"leg {i} turning angle {turning_angle}")
            self.leg[i].rotating(0, turning_angle)
        self.runleg()
        # sleep(dt)
        
    def rotate_y(self, angle): # pitch
        for i in self.leg:
            self.leg[i].rotating(1, angle)
        self.runleg()
        
    def stop_leg(self):
        for i in self.leg:
            self.leg[i].clean()

    def triCycle(self, direction):
        time_on_air = 0.5
        while (self.time <= 1.5 * period):
            if self.time <= period:
                self.leg[0].calculateWalk(self.time, time_on_air, direction)
                self.leg[2].calculateWalk(self.time, time_on_air, direction)
                self.leg[4].calculateWalk(self.time, time_on_air, direction)
            if self.time >= period * 0.45:
                self.leg[1].calculateWalk(self.time - period * 0.5, time_on_air, direction)
                self.leg[3].calculateWalk(self.time - period * 0.5 , time_on_air, direction)
                self.leg[5].calculateWalk(self.time - period * 0.5, time_on_air, direction)
            self.runleg()
            self.time += steps
        self.time = 0

    def waveCycle(self, direction):
        time_on_air = 1/6
        while (self.time <= (11/6) * period):
            if self.time <= period: self.leg[0].calculateWalk(self.time, time_on_air, direction)
            if self.time >= (1/6) * period and self.time <= (7/6) * period: self.leg[5].calculateWalk(self.time - (1/6) * period, time_on_air, direction)
            if self.time >= (2/6) * period and self.time <= (8/6) * period: self.leg[4].calculateWalk(self.time - (2/6) * period, time_on_air, direction)
            if self.time >= (3/6) * period and self.time <= (9/6) * period: self.leg[3].calculateWalk(self.time - (3/6) * period, time_on_air, direction)
            if self.time >= (4/6) * period and self.time <= (10/6) * period: self.leg[2].calculateWalk(self.time - (4/6) * period, time_on_air, direction)
            if self.time >= (5/6) * period and self.time <= (11/6) * period: self.leg[1].calculateWalk(self.time - (5/6) * period, time_on_air, direction)
            self.runleg()
            self.time += steps
        self.time = 0

    def rippleCycle(self, direction):
        time_on_air = 1/6
        while (self.time <= (11/6) * period):
            if self.time <= period: self.leg[0].calculateWalk(self.time, time_on_air, direction)
            if self.time >= (1/6) * period and self.time <= (7/6) * period: self.leg[3].calculateWalk(self.time - (1/6) * period, time_on_air, direction)
            if self.time >= (2/6) * period and self.time <= (8/6) * period: self.leg[5].calculateWalk(self.time - (2/6) * period, time_on_air, direction)
            if self.time >= (3/6) * period and self.time <= (9/6) * period: self.leg[2].calculateWalk(self.time - (3/6) * period, time_on_air, direction)
            if self.time >= (4/6) * period and self.time <= (10/6) * period: self.leg[4].calculateWalk(self.time - (4/6) * period, time_on_air, direction)
            if self.time >= (5/6) * period and self.time <= (11/6) * period: self.leg[1].calculateWalk(self.time - (5/6) * period, time_on_air, direction)
            self.runleg()
            self.time += steps
        self.time = 0

    def biCycle(self, direction):
        time_on_air = 1/3
        while (self.time <= (11/6) * period):
            if self.time <= period: self.leg[2].calculateWalk(self.time, time_on_air, direction)
            if self.time <= period: self.leg[5].calculateWalk(self.time, time_on_air, direction)
            if self.time >= (1/3) * period and self.time <= (4/3) * period: self.leg[4].calculateWalk(self.time - (1/3) * period, time_on_air, direction)
            if self.time >= (1/3) * period and self.time <= (4/3) * period: self.leg[1].calculateWalk(self.time - (1/3) * period, time_on_air, direction)
            if self.time >= (2/3) * period and self.time <= (5/3) * period: self.leg[0].calculateWalk(self.time - (2/3) * period, time_on_air, direction)
            if self.time >= (2/3) * period and self.time <= (5/3) * period: self.leg[3].calculateWalk(self.time - (2/3) * period, time_on_air, direction)
            self.runleg()
            self.time += steps
        self.time = 0

    def tetraCycle(self, direction):
        time_on_air = 1/3
        while (self.time <= (11/6) * period):
            if self.time <= period: self.leg[0].calculateWalk(self.time, time_on_air, direction)
            if self.time <= period: self.leg[3].calculateWalk(self.time, time_on_air, direction)
            if self.time >= (1/3) * period and self.time <= (4/3) * period: self.leg[5].calculateWalk(self.time - (1/3) * period, time_on_air, direction)
            if self.time >= (1/3) * period and self.time <= (4/3) * period: self.leg[1].calculateWalk(self.time - (1/3) * period, time_on_air, direction)
            if self.time >= (2/3) * period and self.time <= (5/3) * period: self.leg[4].calculateWalk(self.time - (2/3) * period, time_on_air, direction)
            if self.time >= (2/3) * period and self.time <= (5/3) * period: self.leg[2].calculateWalk(self.time - (2/3) * period, time_on_air, direction)
            self.runleg()
            self.time += steps
        self.time = 0

    def gaitChange(self, inp):
        self.gait = inp

    def runleg(self):
        for i in self.leg:
            self.leg[i].run()
