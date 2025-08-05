from parameter import *
import maestro
servo = maestro.Controller('/dev/ttyAMA0')

class Leg:
    def __init__(self, leg, c, f, t):
        self.leg = leg             # 0 ~ 5, No. of leg, reference to graph on top
        self.coxa = c              # servo pin for coxa
        self.femur = f             # servo pin for femur
        self.tibia = t             # servo pin for tibia
        self.x = x_offset
        self.y = y_offset
        self.z = z_offset
        self.a = 0                 # angle of coxa
        self.b = 0                # angle of femur
        self.c = 180              # angle of tibia

        self.offset = 0 if self.leg in (2, 5) else 1
        self.offset_angle = offset_angle_map[self.leg]
        self.IK()

    def calculateWalk(self, time, time_on_air, direction):
        distance = 25
        #input()
        if(time <= ((time_on_air)*period)):
            phase = (time * 180)/(period * time_on_air)
            x = direction[1] * distance * (cos(radians(phase)) * -0.5 + 0.5) 
            y = -direction[0] * distance * (cos(radians(phase)) * -0.5 + 0.5)
            self.z = -distance * sin(radians(phase)) + z_offset
            #self.z = -50 + z_offset
        else:
            temp_x = time_on_air * period
            phase = 180 + ((time - temp_x) * 180)/(period - temp_x)
            x = direction[1] * distance * (cos(radians(phase)) * -0.5 + 0.5)
            y = -direction[0] * distance * (cos(radians(phase)) * -0.5 + 0.5)
            self.z = z_offset
        print(self.leg, ",", time, ",", phase)
        # print("position (before transform): ", x,",",y,",",self.z)
        new_vec = transformBodyCoortoLeg(self.leg, [x,y])
        self.x = x_offset + new_vec[0]
        self.y = y_offset + new_vec[1]
        # print("position: ", self.x,",",self.y,",",self.z)
        self.IK()

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

    def rotating(self, type, angle): # type : 0 = roll, 1 = pitch, 2 = yaw (not working yet)
        R_c = R(self.offset, angle, self.offset_angle)[type]
        new_vec = transformBodyCoortoLeg(self.leg, R_c[:2])
        target_x = x_offset + new_vec[0]
        target_y = y_offset + new_vec[1]
        target_z = z_offset + R_c[2]
        #print(f"leg: {self.leg} moving to {target_x, target_y, target_z}\n")
        # self.move_to([target_x, target_y, target_z])

        self.x = target_x
        self.y = target_y
        self.z = target_z
        self.IK()

    def move_to(self, target): # target = [x, y, z]
        dx = (target[0] - self.x) / step
        dy = (target[1] - self.y) / step
        dz = (target[2] - self.z) / step
        for i in range(step):
            self.x += dx
            self.y += dy
            self.z += dz
            #print(f"{i} : Current leg position : {self.x, self.y, self.z}")
            self.IK()
            sleep(delays)

    # to be implemented: find the limit for both ik and actual leg
    ''' 
    def checkValid(self):
        if(self.a>60 or self.a<-60) or (self.b>60 or self.b<-60) or (self.c>180 or self.c<60):
            print("Invalid Input")
            return False
        else:
            return True
    '''

    def IK(self):
        y3 = self.y-ctc[self.offset]
        y2 = sqrt((self.y**2)+(self.x**2))-cl
        theta = atan(self.z/y2)
        l = sqrt((y2**2)+(self.z**2))

        self.a = degrees(atan(self.x/y3))
        self.b = degrees(acos(((fl**2)+(l**2)-(tl**2))/(2*fl*l))-theta)
        self.c = degrees(acos(((fl**2)+(tl**2)-(l**2))/(2*fl*tl)))
        # print("angle: ",self.a,",",self.b,",",self.c)
        self.angleToDC()
        # self.run()

    def angleToDC(self): 
        self.a = int((100 * self.a)/3 + 6000)
        self.b = int((-100 * self.b)/3 + 6000)
        self.c = int((100 * self.c)/3 + 2000)
        # print("polulu output: ",self.a,",",self.b,",",self.c,"\n")

    def clean(self):
        servo.setTarget(self.coxa, 0)
        servo.setTarget(self.femur, 0)
        servo.setTarget(self.tibia, 0)

    def run(self):
        servo.setTarget(self.coxa, self.a)
        servo.setTarget(self.femur, self.b)
        servo.setTarget(self.tibia, self.c)
