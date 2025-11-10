from .parameter import *
# from parameter import *
import traceback

class Leg:
    def __init__(self, leg):
        self.leg = leg             # 0 ~ 5, No. of leg, reference to graph on top
        self.x = x_offset
        self.y = y_offset
        self.z = z_offset
        self.a = 0                 # angle of coxa
        self.b = 0                # angle of femur
        self.c = 180              # angle of tibia

        self.offset = 0 if self.leg in (2, 5) else 1
        self.offset_angle = offset_angle_map[self.leg]
        self.IK()

    def calculateWalk(self, phase, direction, distance, pitch, roll, yaw, rotate):
        if phase <= 180:
            turn_distance = 0.5 * distance
            x = direction[0] * (turn_distance * cos(radians(180 - phase)) + turn_distance)
            y = direction[1] * - (turn_distance * cos(radians(180 - phase)) + turn_distance) 
            self.z = - distance * sin(radians(phase)) + z_offset
        else:
            turn_distance = distance
            x = direction[0] * (-1 * turn_distance * ((phase/180) - 1) + distance)
            y = direction[1] * - (-1 * turn_distance * ((phase/180) - 1) + distance)
            self.z = z_offset
        if not rotate: new_vec = transformBodyCoortoLeg(self.leg, [x,y])
        else: new_vec = [x, y]
        self.x = x_offset + new_vec[0]
        self.y = y_offset + new_vec[1]
        R_c = R(self.offset, self.offset_angle, roll, pitch, yaw, [self.x, self.y]) 
        if phase > 180:
            roll_vec = transformBodyCoortoLeg(self.leg, R_c[0][:2])
            pitch_vec = transformBodyCoortoLeg(self.leg, R_c[1][:2])
            self.x += roll_vec[0] + pitch_vec[0]
            self.y += roll_vec[1] + pitch_vec[1]
            self.z += R_c[0][2] + R_c[1][2]
        yaw_vec = R_c[2][:2]
        self.x += yaw_vec[0]
        self.y += yaw_vec[1]
        self.IK()
        self.angleToDC()
        return (self.a, self.b, self.c)

    def stand(self,l,c):
        self.IK()
        d = 20 - (20/l)*c
        self.b += d
        self.c += d
        self.angleToDC()
        return (self.a, self.b, self.c)

    def balance(self, pitch, roll): 
        R_c = R(self.offset, self.offset_angle, roll, pitch) 
        roll_vec = transformBodyCoortoLeg(self.leg, R_c[0][:2])
        pitch_vec = transformBodyCoortoLeg(self.leg, R_c[1][:2])
        self.x = x_offset + roll_vec[0] + pitch_vec[0]
        self.y = y_offset + roll_vec[1] + pitch_vec[1]
        self.z = z_offset + R_c[0][2] + R_c[1][2]
        self.IK()
        self.angleToDC()
        return (self.a, self.b, self.c)

    def IK(self):
        try:
            y = sqrt(self.x**2 + self.y**2) - cl # actual location of tip from femur in coxa frame
            k = sqrt(y**2 + self.z**2) # shortest distance from femur to tibia tip 
            
            if k < 1e-6:
                k = 1
                # raise ValueError("Target too close to femur pivot.")
            elif k > fl + tl or k < abs(fl - tl):
                k = fl + tl
            elif k < abs(fl - tl)
                k = abs(fl - tl)
                # raise ValueError("Target out of reachable workspace.")
            
            theta = asin(max(-1, min(1, self.z / k))) # angle between horizontal and k
            theta2 = acos(max(-1, min(1, ((fl**2)+(k**2)-(tl**2))/(2*fl*k)))) # cosine angle of tibia

            self.a = max(min(coxa_range[1], degrees(atan2(self.x, self.y))), coxa_range[0]) # coxa angle
            self.b = max(min(femur_range[1], degrees(theta2 - theta)), femur_range[0]) # femur angle

            self.c = max(min(tibia_range[1], 180 - degrees(acos(max(-1, min(1, ((fl**2)+(tl**2)-(k**2))/(2*fl*tl)))))), tibia_range[0]) # tibia angle from femur
            # if self.a > coxa_range[1] or self.a < coxa_range[0] or self.b > femur_range[1] or self.b < femur_range[0] or self.c > tibia_range[1] or self.c < tibia_range[0]:
                # raise ValueError("Angle exceeded.")
        except Exception as e:
            traceback.print_exc()
            self.a = 0
            self.b = 0
            self.c = 0
        
    def angleToDC(self): # 4000 - 8000
        self.a = int((100 * self.a)/3 + 6000)
        self.b = int((100 * self.b)/3 + 6000)
        self.c = int((100 * self.c)/3 + 3000)

    def curr_angle(self):
        return (self.a, self.b, self.c)
