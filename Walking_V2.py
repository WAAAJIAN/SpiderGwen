from math import *
import maestro
import datetime

servo = maestro.Controller('/dev/ttyAMA0')

#stand = [[0,200,60]*3]
# need settle the position for each leg in case of stand/walk, and make height customisable

period = 30000   # period of a leg cycle (its not time!)
x_offset = 0     # initial x position of leg (vertical axis)
y_offset = 150   # initial y position of leg (horizontal axis from the center)
z_offset = 130   # initial z position of leg (height of bot)
steps = 1500     # speed of motion

ctc = 81   # length from center to coxa
cl = 32.44 # length of coxa
fl = 75    # length of femur
tl = 160   # length of tibia

leg_max_length = 358.44 # maximum y position that leg can go to

#Matrix for transform coordinate on each leg
M0 = [[sin(radians(30)), cos(radians(30))], 
     [sin(radians(60)), -cos(radians(60))]]   # leg 0
M1 = [[sin(radians(30)), cos(radians(30))],
     [-sin(radians(60)), cos(radians(60))]]   # leg 1
M2 = [[1, 0], 
     [0, 1]]                                  # leg 2
M3 = [[sin(radians(30)), -cos(radians(30))],
     [sin(radians(60)), cos(radians(60))]]    # leg 3
M4 = [[sin(radians(30)), -cos(radians(30))],
     [-sin(radians(60)), -cos(radians(60))]]  # leg 4
M5 = [[1, 0], 
     [0, -1]]                                 # leg 5
transformMat = {0: M0, 1: M1, 2: M2, 3: M3, 4: M4, 5: M5}

def vectorMull(m1, m2): # transform vector (Matrix Multiplication)
    m3 = [(m1[0][0])*(m2[0]) + (m1[0][1])*(m2[1]), (m1[1][0])*(m2[0]) + (m1[1][1])*(m2[1])]
    #print(m1," x ", m2," = ",m3)
    return m3

def polarVector(angle, value = 1):
    return [value * cos(radians(angle)), value * sin(radians(angle))]

class Spider:
    def __init__(self):
        self.leg = {0: TriLeg(0,0,0,0,1,2), 1: TriLeg(1,1,0,3,4,5), 2: TriLeg(2,1,1,6,7,8), 3: TriLeg(3,1,2,9,10,11), 4: TriLeg(4,0,2,18,19,20), 5: TriLeg(5,0,1,21,22,23)}
        #self.leg = [TriLeg(0,0,0,0,1,2), TriLeg(1,1,0,3,4,5)]                   # front leg
        #self.leg = [TriLeg(0,1,1,6,7,8),TriLeg(0,0,1,21,22,23)]                 # middle leg
        #self.leg =  [TriLeg(1,1,2,9,10,11),TriLeg(0,0,2,18,19,20)]              # back leg
        #self.leg = [TriLeg(0,0,0,0,1,2),TriLeg(0,1,1,6,7,8),TriLeg(0,0,2,18,19,20)]
        #self.leg = [TriLeg(0,0,0,0,1,2)]
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
        #self.leg_y = y_offset + ctc
        ##self.direction = 1 # 1 is +ve anticlock, -1 is -ve clock
        self.gaitFunction = {0: self.triCycle, 1: self.waveCycle, 2: self.rippleCycle, 3: self.biCycle, 4: self.tetraCycle}
        self.gait = 1

    '''
    def Walk(self,loop):
        curr = loop
        print("Phase 0\n")
        self.gaitFunction[self.gait](0)
        print("Phase 1\n")
        while(curr > 0):
            self.gaitFunction[self.gait](1)
            curr -= 1
        print("Phase 2\n")
        self.gaitFunction[self.gait](2)
    '''

    def triCycle(self, direction):
        time_on_air = 0.5
        while (self.time <= 1.5 * period):
            if self.time <= period:
                self.leg[0].calculateWalk(self.time, time_on_air, direction)
                self.leg[2].calculateWalk(self.time, time_on_air, direction)
                self.leg[4].calculateWalk(self.time, time_on_air, direction)
            if self.time >= period * 0.5:
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

class TriLeg:
    def __init__(self, leg, facing, pos, c, f, t):
        self.leg = leg             # 0 ~ 5, No. of leg, reference to graph on top
        self.facing = facing       # 0 for left, 1 for right
        self.pos = pos             # 0 for front, 1 for middle, 2 for back
        self.coxa = c              # servo pin for coxa
        self.femur = f             # servo pin for femur
        self.tibia = t             # servo pin for tibia
        self.x = x_offset
        self.y = y_offset
        self.z = z_offset
        self.a = 0                 # angle of coxa
        self.b = 0                 # angle of femur
        self.c = 180               # angle of tibia

    def calculateWalk(self, time, time_on_air, direction):
        distance = 25
        #input()
        if(time <= ((time_on_air)*period)):
            phase = (time * 180)/(period * time_on_air)
            self.x = direction[1] * distance * (cos(radians(phase)) * -0.5 + 0.5) + x_offset
            self.y = -direction[0] * distance * (cos(radians(phase)) * -0.5 + 0.5) + y_offset
            #self.z = -distance * sin(radians(phase)) + z_offset
            self.z = -50 + z_offset
        else:
            temp_x = time_on_air * period
            phase = 180 + ((time - temp_x) * 180)/(period - temp_x)
            self.x = direction[1] * distance * (cos(radians(phase)) * -0.5 + 0.5) + x_offset
            self.y = -direction[0] * distance * (cos(radians(phase)) * -0.5 + 0.5) + y_offset
            self.z = z_offset
        print(self.leg, ",", time, ",", phase)
        print("position (before transform): ", self.x,",",self.y,",",self.z)
        self.transformCoor()
        print("position: ", self.x,",",self.y,",",self.z)
        self.IK()
        self.run()

    '''
    def calculateWalk(self, type, time): # 0 : start, 1 : moving, 2 : end
        phase = (time/(0.5*period)) * 360
        distance = 25
        #input()
        \'''
        if(time <= (0.25*period)):
            if type == 0:
                self.x = - (distance*cos(radians(phase)) + x_offset - distance)
                self.y = y_offset
                self.z = -distance*sin(radians(phase)) + z_offset
            elif type == 1:
                self.x = -2*distance*cos(radians(phase))
                self.y = y_offset
                self.z = - 2*distance*sin(radians(phase)) + z_offset
            else:
                self.x = - distance*(cos(radians(phase)) + 1)
                self.y = y_offset
                self.z = - distance*sin(radians(phase)) + z_offset
        \'''
        if(time <= (0.25*period)):
            if type == 0:
                self.x = - (distance*cos(radians(phase)) + x_offset - distance)
                self.y = y_offset
                self.z = - 50 + z_offset
            elif type == 1:
                self.x = -2*distance*cos(radians(phase))
                self.y = y_offset
                self.z = - 50 + z_offset
            else:
                self.x = - distance*(cos(radians(phase)) + 1)
                self.y = y_offset
                self.z = - 50 + z_offset
        else:
            if type == 0 or type == 1:
                self.x = -2*distance*cos(radians(phase))
                self.z = z_offset
                self.y = y_offset
        #print(phase)
        #print([self.facing, self.pos], "position (before transform): ", self.x,",",self.y,",",self.z)
        self.transformCoor()
        #print([self.facing, self.pos], "position: ", self.x,",",self.y,",",self.z)
        self.IK()
        self.run()
    '''

    def transformCoor(self):
        self.y -= y_offset
        newVec = vectorMull(transformMat[self.leg], [self.y, self.x])
        self.y = newVec[0] + y_offset
        self.x = newVec[1]

    '''
    def checkValid(self):
        if(self.a>60 or self.a<-60) or (self.b>60 or self.b<-60) or (self.c>180 or self.c<60):
            print("Invalid Input")
            return False
        else:
            return True
    '''

    def IK(self):
        y3 = self.y-ctc
        y2 = sqrt((self.y**2)+(self.x**2))-cl
        theta = atan(self.z/y2)
        l = sqrt((y2**2)+(self.z**2))

        self.a = degrees(atan(self.x/y3))
        self.b = degrees(acos(((fl**2)+(l**2)-(tl**2))/(2*fl*l))-theta)
        self.c = degrees(acos(((fl**2)+(tl**2)-(l**2))/(2*fl*tl)))
        print("angle: ",self.a,",",self.b,",",self.c)

    def angleToDC(self):
        self.a = int((100 * self.a)/3 + 6000)
        self.b = int((-100 * self.b)/3 + 6000)
        self.c = int((100 * self.c)/3 + 2000)
        print("output: ",self.a,",",self.b,",",self.c,"\n")

    def run(self):
        self.angleToDC()
        servo.setTarget(self.coxa, self.a)
        servo.setTarget(self.femur, self.b)
        servo.setTarget(self.tibia, self.c)

def delay(ms):
    start_time = datetime.datetime.now()
    target_time = start_time + datetime.timedelta(milliseconds=ms)
    while datetime.datetime.now() < target_time:
        pass

def main():
    girl = Spider()
    while(1):
        inp = input("enter: ")
        if inp == 'w' : girl.gaitFunction[girl.gait]([0,1])
        elif inp == 'd' : girl.gaitFunction[girl.gait]([1,0])
        elif inp == 's' : girl.gaitFunction[girl.gait]([0,-1])
        elif inp == 'a' : girl.gaitFunction[girl.gait]([-1,0])
        elif inp == 'e' : girl.gaitFunction[girl.gait](polarVector(45))
        elif inp == 'q' : girl.gaitFunction[girl.gait](polarVector(135))
        elif inp == '0' : girl.gaitChange(0)
        elif inp == '1' : girl.gaitChange(1)
        elif inp == '2' : girl.gaitChange(2)
        elif inp == '3' : girl.gaitChange(3)
        elif inp == '4' : girl.gaitChange(4)

main()