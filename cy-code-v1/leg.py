from parameter import *
import maestro
servo = maestro.Controller('/dev/ttyAMA0')
import traceback

class Leg:
    def __init__(self, leg, c, f, t):
        self.leg = leg             # 0 ~ 5, No. of leg, reference to graph on top
        self.coxa = c              # servo pin for coxa
        self.femur = f             # servo pin for femur
        self.tibia = t             # servo pin for tibia
        self.x = x_offset
        self.y = y_offset
        self.z = z_offset
        self.x_start = self.x
        self.y_start = self.y
        self.y_start = self.z
        self.a = 0                 # angle of coxa
        self.b = 0                # angle of femur
        self.c = 180              # angle of tibia

        self.offset = 0 if self.leg in (2, 5) else 1
        self.offset_angle = offset_angle_map[self.leg]
        self.IK()

    def walknbalance(self, phase, direction, distance, type_, pitch, roll):
        if phase <= 180:
            turn_distance = walk_cycle["on_air"][type_] * distance
            x = direction[1] * turn_distance * (cos(radians(phase)) * -0.5 + 0.5) - (distance if type_ > 0 else 0)
            y = -direction[0] * turn_distance * (cos(radians(phase)) * -0.5 + 0.5)
            self.z = - distance * sin(radians(phase)) + z_offset
        else:
            turn_distance = walk_cycle["on_ground"][type_] * distance
            x = direction[1] * turn_distance * (cos(radians(phase)) * -0.5 + 0.5) - (distance if type_ < 2 else 0)
            y = -direction[0] * turn_distance * (cos(radians(phase)) * -0.5 + 0.5)
            self.z = z_offset
        new_vec = transformBodyCoortoLeg(self.leg, [x,y])
        self.x = x_offset + new_vec[0]
        self.y = y_offset + new_vec[1]
        if phase > 180:
            R_c = R(self.offset, self.offset_angle, roll, pitch) 
            roll_vec = transformBodyCoortoLeg(self.leg, R_c[0][:2])
            pitch_vec = transformBodyCoortoLeg(self.leg, R_c[1][:2])
            self.x += roll_vec[0] + pitch_vec[0]
            self.y += roll_vec[1] + pitch_vec[1]
            self.z += R_c[0][2] + R_c[1][2]
        print(f"leg: {self.leg} in {phase} has x = {x}, y = {y}, moving to {self.x, self.y}")
        self.IK()

    def calculateWalk(self, phase, direction, distance, type_):
        if phase <= 180:
            turn_distance = walk_cycle["on_air"][type_] * distance
            x = direction[1] * (turn_distance * cos(radians(180 - phase)) + distance * walk_offset[type_]) 
            y = direction[0] * - (turn_distance * cos(radians(180 - phase)) + distance * walk_offset[type_]) 
            self.z = - distance * sin(radians(phase)) + z_offset
        else:
            turn_distance = walk_cycle["on_ground"][type_] * distance
            x = direction[1] * (-1 * turn_distance * ((phase/180) - 1) + (distance if type_ < 2 else 0)) 
            y = direction[0] * - (-1 * turn_distance * ((phase/180) - 1) + (distance if type_ < 2 else 0)) 
            self.z = z_offset
        new_vec = transformBodyCoortoLeg(self.leg, [x,y])
        self.x = x_offset + new_vec[0]
        self.y = y_offset + new_vec[1]
        print(f"leg: {self.leg} in {phase} on type {type_} has x = {x}, y = {y}, moving to {self.x, self.y}")
        self.IK()

    # def rotating(self, type_, angle): # type : 0 = roll, 1 = pitch, 2 = yaw (not working yet)
    #     R_c = R(self.offset, angle, self.offset_angle)[type_]
    #     new_vec = transformBodyCoortoLeg(self.leg, R_c[:2])
    #     target_x = x_offset + new_vec[0]
    #     target_y = y_offset + new_vec[1]
    #     target_z = z_offset + R_c[2]
    #     print(f"leg: {self.leg} with {angle} moving to {target_x, target_y, target_z}")
    #     # self.move_to([target_x, target_y, target_z])

    #     self.x = target_x
    #     self.y = target_y
    #     self.z = target_z
    #     self.IK()

    def rotating(self, pitch, roll): 
        R_c = R(self.offset, self.offset_angle, roll, pitch) 
        roll_vec = transformBodyCoortoLeg(self.leg, R_c[0][:2])
        pitch_vec = transformBodyCoortoLeg(self.leg, R_c[1][:2])
        self.x = x_offset + roll_vec[0] + pitch_vec[0]
        self.y = y_offset + roll_vec[1] + pitch_vec[1]
        self.z = z_offset + R_c[0][2] + R_c[1][2]
        # print(f"leg: {self.leg} with {roll, pitch} moving to {self.x, self.y, self.z}")
        self.IK()

    # def move_to(self, target): # target = [x, y, z], to use for manual rotate only
    #     dx = (target[0] - self.x) / step
    #     dy = (target[1] - self.y) / step
    #     dz = (target[2] - self.z) / step
    #     for i in range(step):
    #         self.x += dx
    #         self.y += dy
    #         self.z += dz
    #         # print(f"{i} : Current leg position : {self.x, self.y, self.z}")
    #         self.IK()
    #         sleep(delays)

    def IK(self):
        try:
            y = sqrt(self.x**2 + self.y**2) - cl # actual location of tip from femur in coxa frame
            k = sqrt(y**2 + self.z**2) # shortest distance from femur to tibia tip 
            
            if k < 1e-6:
                raise ValueError("Target too close to femur pivot.")
            elif k > fl + tl or k < abs(fl - tl):
                raise ValueError("Target out of reachable workspace.")
            
            theta = asin(max(-1, min(1, self.z / k))) # angle between horizontal and k
            theta2 = acos(max(-1, min(1, ((fl**2)+(k**2)-(tl**2))/(2*fl*k)))) # cosine angle of tibia

            self.a = degrees(atan2(self.x, self.y)) # coxa angle
            self.b = degrees(theta2 - theta) # femur angle

            self.c = 180 - degrees(acos(max(-1, min(1, ((fl**2)+(tl**2)-(k**2))/(2*fl*tl))))) # tibia angle from femur
            print(f"Current angle: {self.a, self.b, self.c} \n")
            if self.a > coxa_range[1] or self.a < coxa_range[0] or self.b > femur_range[1] or self.b < femur_range[0] or self.c > tibia_range[1] or self.c < tibia_range[0]:
                print(f"angle exceed with {self.a, self.b, self.c}")
                raise ValueError("Angle exceeded.")
        except Exception as e:
            traceback.print_exc()
            self.a = 0
            self.b = 0
            self.c = 0
        self.angleToDC()
        
    def angleToDC(self): # 4000 - 8000
        self.a = int((100 * self.a)/3 + 6000)
        self.b = int((100 * self.b)/3 + 6000)
        self.c = int((100 * self.c)/3 + 3000)

    def clean(self):
        servo.setTarget(self.coxa, 0)
        servo.setTarget(self.femur, 0)
        servo.setTarget(self.tibia, 0)

    def run(self):
        servo.setTarget(self.coxa, self.a)
        servo.setTarget(self.femur, self.b)
        servo.setTarget(self.tibia, self.c)
