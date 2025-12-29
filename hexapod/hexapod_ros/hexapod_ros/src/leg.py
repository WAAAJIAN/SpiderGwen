from .parameter import *
import traceback

class Leg:
    """
    Handles Inverse Kinematics (IK) for a single leg.
    Translates (X, Y, Z) coordinates into (Coxa, Femur, Tibia) servo angles.
    """
    def __init__(self, leg):
        self.leg = leg # 0 ~ 5, No. of leg, reference to graph in parameter file
        # Foot position relative to leg base
        self.x, self.y, self.z = x_offset, y_offset, z_offset
        # Joint angles (coxa, femur, tibia)
        self.a, self.b, self.c = 0, 0, 180
        self.offset_angle = offset_angle_map[self.leg]
        self.IK()

    def calculateWalk(self, phase, direction, distance, pitch, roll, yaw, rotate):
        """ Swing motion, leg tip will draw a semicircle, motion integrated with balance"""
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
        if not rotate: new_vec = transformLegtoBody(self.leg, [x,y])
        else: new_vec = [x, y]
        self.x = x_offset + new_vec[0]
        self.y = y_offset + new_vec[1]
        R_c = R(self.offset, self.offset_angle, roll, pitch, yaw, [self.x, self.y]) 
        if phase > 180:
            roll_vec = transformLegtoBody(self.leg, R_c[0][:2])
            pitch_vec = transformLegtoBody(self.leg, R_c[1][:2])
            self.x += roll_vec[0] + pitch_vec[0]
            self.y += roll_vec[1] + pitch_vec[1]
            self.z += R_c[0][2] + R_c[1][2]
        yaw_vec = transformLegtoBody(self.leg, R_c[2][:2])
        self.x += yaw_vec[0]
        self.y += yaw_vec[1]
        self.IK()
        self.verify_IK()
        self.angleToDC()
        return (self.a, self.b, self.c)

    def stand(self,l,c): # stand up function (brute force)
        self.IK()
        d = 20 - (20/l)*c
        self.b += d
        self.c += d
        self.verify_IK()
        self.angleToDC()
        return (self.a, self.b, self.c)

    def balance(self, pitch, roll): # only roll & pitch, no yaw
        R_c = R(self.offset, self.offset_angle, roll, pitch) 
        roll_vec = transformLegtoBody(self.leg, R_c[0][:2])
        pitch_vec = transformLegtoBody(self.leg, R_c[1][:2])
        self.x = x_offset + roll_vec[0] + pitch_vec[0]
        self.y = y_offset + roll_vec[1] + pitch_vec[1]
        self.z = z_offset + R_c[0][2] + R_c[1][2]
        self.IK()
        self.verify_IK()
        self.angleToDC()
        return (self.a, self.b, self.c)
    
    @staticmethod
    def FK(joint_angles, DH_table):
        # find end effector positoin given joint angles
        theta1, theta2, theta3 = joint_angles
        H0_1 = H(DH_table[0][0], DH_table[0][1], DH_table[0][2], radians(theta1))
        H1_2 = H(DH_table[1][0], DH_table[1][1], DH_table[1][2], radians(theta2))
        H2_3 = H(DH_table[2][0], DH_table[2][1], DH_table[2][2], radians(theta3))
        H0_2 = H0_1@H1_2
        H0_3 = H0_2@H2_3
        x, y, z = H0_3[0][3], H0_3[1][3], H0_3[2][3]  # extract position vector
        return (x, y, z)   
    
    def verify_IK(self):
        target = (self.x, self.y, self.z)
        fk_pos = Leg.FK((self.a, self.b, self.c), DH_table)
        error = (
            fk_pos[0] - target[0],
            fk_pos[1] - target[1],
            fk_pos[2] - target[2]
        )

        print("Target:", target)
        print("FK:", fk_pos)
        print("Error:", error)

        if any(abs(e) > 1e-2 for e in error):
            print("IK verification failed")
   
    def IK(self):
        """
        Inverse Kinematics: 
        Calculates servo angles (self.a, self.b, self.c) from desired (self.x, self.y, self.z) foot position.
        """
        try:
            y = sqrt(self.x**2 + self.y**2) - cl # actual location of tip from femur in coxa frame
            k = sqrt(y**2 + self.z**2) # shortest distance from femur to tibia tip 
            
            # Constrain k to reachable workspace
            k = max(abs(fl - tl), min(fl + tl, k))
            
            theta = asin(max(-1, min(1, self.z / k))) # angle between horizontal and k
            theta2 = acos(max(-1, min(1, ((fl**2)+(k**2)-(tl**2))/(2*fl*k)))) # cosine angle of tibia

            self.a = max(min(coxa_range[1], degrees(atan2(self.x, self.y))), coxa_range[0]) # coxa angle
            self.b = max(min(femur_range[1], degrees(theta2 - theta)), femur_range[0]) # femur angle
            self.c = max(min(tibia_range[1], 180 - degrees(acos(max(-1, min(1, ((fl**2)+(tl**2)-(k**2))/(2*fl*tl)))))), tibia_range[0]) # tibia angle from femur
        except Exception:
            traceback.print_exc()
            self.a = self.b = self.c = 0
        
    def angleToDC(self):
        """Converts raw degrees to Servo Duty Cycle (PWM) values. (4000 ~ 8000)"""
        self.a = int((100 * self.a)/3 + 6000)
        self.b = int((100 * self.b)/3 + 6000)
        self.c = int((100 * self.c)/3 + 3000)

    def curr_angle(self):
        return (self.a, self.b, self.c)

