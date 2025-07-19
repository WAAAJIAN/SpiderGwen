import maestro
from leg_config import Config as cfg
import numpy as np
import ForwardKinematics
from math import *

ServoController = maestro.Controller('/dev/ttyAMA0')

min_angle = -120
max_angle = 120

class Trileg:
    def __init__(self, leg, sc, sf, st, coxa_deg, femur_deg, tibia_deg):
        self.leg = leg # name of the leg (e.g., 'L1', 'L2', 'L3, 'R1', 'R2', 'R3')
        self.sc = sc # servo pin for coxa
        self.sf = sf # servo pin for femur
        self.st = st # servo pin for tibia
        self.coxa_deg = coxa_deg
        self.femur_deg = femur_deg
        self.tibia_deg = tibia_deg

    def angleToDC(self):
        self.coxa_pwm = int((100 * self.coxa_deg)/3 + 6000)
        self.femur_pwm = int((100 * self.femur_deg)/3 + 6000)
        self.tibia_pwm = int((-100 * self.tibia_deg)/3 + 8000)
        print(f"coxa {self.leg}: {self.coxa_pwm}")
        print(f"femur {self.leg}: {self.femur_pwm}")
        print(f"tibia {self.leg}: {self.tibia_pwm}")
    
    def move(self):
        self.angleToDC()
        ServoController.setTarget(self.sc, self.coxa_pwm)
        ServoController.setTarget(self.sf, self.femur_pwm)
        ServoController.setTarget(self.st, self.tibia_pwm)

    def clean(self):
        ServoController.setTarget(self.sc, 0)
        ServoController.setTarget(self.sf, 0)
        ServoController.setTarget(self.st, 0)

    def clamp(self, x, min_val, max_val):
        return max(min_val, min(x, max_val))

    # def IK(self, global_x, global_y, global_z):
    #     x, y, z = ForwardKinematics.global_to_leg_frame(self.leg, global_x, global_y, global_z)  #local positions of the leg
    #     # Step 1: Coxa angle
    #     theta1 = np.arctan2(y, x)

    #     # Step 2: Projection into sagittal plane
    #     r = np.sqrt(x**2 + y**2)
    #     x_ = r - cfg.l_coxa
    #     z_ = z
    #     d = np.sqrt(x_**2 + z_**2)

    #     # # Step 3: Check reachability
    #     d = self.clamp(d, 1e-6, cfg.l_femur + cfg.l_tibia + 1e-6)

    #     # Step 4: Compute angles using Law of Cosines
    #     alpha = np.arccos(self.clamp((cfg.l_femur**2 + cfg.l_tibia**2 - d**2) / (2 * cfg.l_femur * cfg.l_tibia), -1, 1))
    #     # In Trileg.py -> IK function
    #     theta3 = alpha - np.pi 
    #     beta = np.arccos(self.clamp((cfg.l_femur**2 + d**2 - cfg.l_tibia**2) / (2 * cfg.l_femur * d), -1, 1))
    #     gamma = np.arctan2(z_, x_)
    #     theta2 = gamma - beta

    #     print(f"IK input after transform: x_ = {x_:.2f}, z_ = {z_:.2f}, gamma = {degrees(gamma):.2f}")
        
    #     self.coxa_deg = self.clamp(np.degrees(theta1), min_angle, max_angle)
    #     self.femur_deg = self.clamp(np.degrees(theta2), min_angle, max_angle)
    #     self.tibia_deg = self.clamp(np.degrees(theta3), min_angle, max_angle)

    #     print(f"gamma = {np.degrees(gamma):.2f}, beta = {np.degrees(beta):.2f}, alpha = {np.degrees(alpha):.2f}")

    def IK(self, global_x, global_y, global_z):
        x, y, z = ForwardKinematics.global_to_leg_frame(self.leg, global_x, global_y, global_z)
        
        theta1 = np.arctan2(y, x)

        # Step 2: Projection into the leg's vertical (sagittal) plane
        r = np.sqrt(x**2 + y**2)
        x_ = r - cfg.l_coxa  # Horizontal distance from femur pivot to foot
        z_ = z               # Vertical distance from femur pivot to foot
        d = np.sqrt(x_**2 + z_**2) # Straight-line distance from femur pivot to foot

        # Step 3: Check reachability and clamp to prevent math errors
        if d > (cfg.l_femur + cfg.l_tibia):
            d = cfg.l_femur + cfg.l_tibia - 1e-6 # Clamp to max reach
        if d < abs(cfg.l_femur - cfg.l_tibia):
            d = abs(cfg.l_femur - cfg.l_tibia) + 1e-6 # Clamp to min reach

        # Step 4: Compute angles using Law of Cosines
        alpha = np.arccos(self.clamp((cfg.l_femur**2 + cfg.l_tibia**2 - d**2) / (2 * cfg.l_femur * cfg.l_tibia), -1.0, 1.0))
        beta = np.arccos(self.clamp((cfg.l_femur**2 + d**2 - cfg.l_tibia**2) / (2 * cfg.l_femur * d), -1.0, 1.0))
        gamma = np.arctan2(z_, x_)

        theta2 = beta - gamma

        theta3 = np.pi - alpha
        
        # Set the final clamped angles in degrees
        self.coxa_deg = self.clamp(np.degrees(theta1), min_angle, max_angle)
        self.femur_deg = self.clamp(np.degrees(theta2), min_angle, max_angle)
        self.tibia_deg = self.clamp(np.degrees(theta3), min_angle, max_angle)

        print(f"gamma = {np.degrees(gamma):.2f}, beta = {np.degrees(beta):.2f}, alpha = {np.degrees(alpha):.2f}")