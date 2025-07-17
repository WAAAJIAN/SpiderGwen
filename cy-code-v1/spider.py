from parameter import *
from leg import *

class Spider:
    def __init__(self):
        # self.leg = {5: Leg(5,3,4,5)}
        #self.leg = {2 : Leg(2, 18, 19, 20)}
        self.leg = {
            0: Leg(0, 0, 1, 2), 
            5: Leg(5, 3, 4, 5), 
            4: Leg(4, 6, 7, 8), 
            1: Leg(1, 21, 22, 23), 
            2: Leg(2, 18, 19, 20), 
            3: Leg(3, 9, 10, 11)
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

    def rotate_x(self, angle):
        for i in self.leg:
            print(i)
            if i == 0 or i == 5 or i == 4: 
                angle = -angle
            print(f"leg {i} turning angle {angle}")
            self.leg[i].rotating(0, angle)
        
    def stop_leg(self):
        for i in self.leg:
            self.leg[i].clean()

    def triCycle(self, direction):
        time_on_air = 0.5
        while (self.time <= 1.5 * period):
            if self.time <= period:
                pass
                self.leg[0].calculateWalk(self.time, time_on_air, direction)
                self.leg[2].calculateWalk(self.time, time_on_air, direction)
                self.leg[4].calculateWalk(self.time, time_on_air, direction)
            if self.time >= period * 0.5:
                pass
                self.leg[1].calculateWalk(self.time - period * 0.5, time_on_air, direction)
                self.leg[3].calculateWalk(self.time - period * 0.5 , time_on_air, direction)
                self.leg[5].calculateWalk(self.time - period * 0.5, time_on_air, direction)
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
            self.time += steps
        self.time = 0

    def gaitChange(self, inp):
        self.gait = inp

def main():
    gwen = Spider()
    try:
        while(1):
            # inp = input("enter: ")
            # if inp == 'w' : gwen.gaitFunction[gwen.gait]([0,1])
            # elif inp == 'd' : gwen.gaitFunction[gwen.gait]([1,0])
            # elif inp == 's' : gwen.gaitFunction[gwen.gait]([0,-1])
            # elif inp == 'a' : gwen.gaitFunction[gwen.gait]([-1,0])
            # elif inp == 'e' : gwen.gaitFunction[gwen.gait](polarVector(45))
            # elif inp == 'q' : gwen.gaitFunction[gwen.gait](polarVector(135))
            # elif inp == '0' : gwen.gaitChange(0)
            # elif inp == '1' : gwen.gaitChange(1)
            # elif inp == '2' : gwen.gaitChange(2)
            # elif inp == '3' : gwen.gaitChange(3)
            # elif inp == '4' : gwen.gaitChange(4)

            angle = int(input("enter angle:"))
            gwen.rotate_x(angle)

    except KeyboardInterrupt:
        print("Stopping Spider.....")
        gwen.stop_leg()

main()