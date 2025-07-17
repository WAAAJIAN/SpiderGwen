import maestro
from leg_config import Config as cfg
import numpy as np
import ForwardKinematics

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

    def IK(self, global_x, global_y, global_z):
        x, y, z = ForwardKinematics.global_to_leg_frame(self.leg, global_x, global_y, global_z)  #local positions of the leg
        # Step 1: Coxa angle
        theta1 = np.arctan2(y, x)

        # Step 2: Projection into sagittal plane
        r = np.sqrt(x**2 + y**2)
        x_ = r - cfg.l_coxa
        z_ = z
        d = np.sqrt(x_**2 + z_**2)

        # # Step 3: Check reachability
        d = self.clamp(d, 1e-6, cfg.l_femur + cfg.l_tibia + 1e-6)

        # Step 4: Compute angles using Law of Cosines
        alpha = np.arccos(self.clamp((cfg.l_femur**2 + cfg.l_tibia**2 - d**2) / (2 * cfg.l_femur * cfg.l_tibia), -1, 1))
        theta3 = np.pi - alpha 
        beta = np.arccos(self.clamp((cfg.l_femur**2 + d**2 - cfg.l_tibia**2) / (2 * cfg.l_femur * d), -1, 1))
        gamma = np.arctan2(z_, x_)
        theta2 = beta - gamma

        self.coxa_deg = self.clamp(np.degrees(theta1), min_angle, max_angle)
        self.femur_deg = self.clamp(np.degrees(theta2), min_angle, max_angle)
        self.tibia_deg = self.clamp(np.degrees(theta3), min_angle, max_angle)

        print(f"[{self.leg}] x={x:.2f}, y={y:.2f}, z={z:.2f}, r={r:.2f}, x_={x_:.2f}, z_={z_:.2f}, d={d:.2f}")
        print(f"theta1 = {np.degrees(theta1):.2f}, gamma = {np.degrees(gamma):.2f}, beta = {np.degrees(beta):.2f}, alpha = {np.degrees(alpha):.2f}")

    # #### IK from the paper ####
    # def IK_paper(self, global_x, global_y, global_z):
    #     x, y, z = ForwardKinematics.global_to_leg_frame(self.leg, global_x, global_y, global_z)  # local leg frame
    #     theta1 = np.arctan2(y, x)

    #     reach = np.sqrt(x**2 + y**2 + z**2)
    #     max_reach = cfg.l_coxa + cfg.l_femur + cfg.l_tibia
    #     if reach > max_reach:
    #         print(f"[{self.leg}] Unreachable pose! Distance: {reach:.2f}, Max: {max_reach:.2f}")
    #         return

    #     # Paper-derived projection variables
    #     coxiaX = cfg.l_coxa
    #     femurX = cfg.l_femur
    #     femurH = 0  # assuming zero lateral offset for planar IK
    #     tibiaX = cfg.l_tibia
    #     tibiaH = 0  # same assumption

    #     # Step 1: a, used for θ2
    #     a = (x * np.cos(theta1) - coxiaX + y * np.sin(theta1))
    #     pz = z

    #     # Step 2: theta2 from atan2-form
    #     b = 2 * tibiaH * a + 2 * pz * tibiaX
    #     c = -2 * tibiaX * a + 2 * pz * tibiaH
    #     d = np.sin(0) * b + np.cos(0) * c  # start with θ2 ≈ 0 assumption for d
    #     # Full atan2 chain (Equation 18)
    #     theta2 = np.arctan2(b, c) + np.arctan2(np.sqrt(b**2 + c**2 - d**2), d)

    #     # Step 3: theta3 from atan2-form (Equation 22)
    #     A = femurX
    #     B = femurH
    #     C = (np.sin(theta2) * coxiaX - z * np.cos(theta2) -
    #         x * np.cos(theta1) * np.sin(theta2) -
    #         y * np.sin(theta1) * np.sin(theta2) - tibiaH)
        
    #     radicand = A**2 + B**2 - C**2
    #     print(f"A² + B² - C² = {radicand:.2f}")
    #     theta3 = np.arctan2(A, B) + np.arctan2(np.sqrt(A**2 + B**2 - C**2), C)

    #     # Convert to degrees and clamp
    #     self.coxa_deg = self.clamp(np.degrees(theta1), min_angle, max_angle)
    #     self.femur_deg = self.clamp(np.degrees(theta2), min_angle, max_angle)
    #     self.tibia_deg = self.clamp(np.degrees(theta3), min_angle, max_angle)

    #     # self.coxa_deg = np.degrees(theta1)
    #     # self.femur_deg = np.degrees(theta2)
    #     # self.tibia_deg = np.degrees(theta3)

    #     print(f"[{self.leg}] x={x:.2f}, y={y:.2f}, z={z:.2f}, a={a:.2f}")
    #     # print(f"θ1 = {np.degrees(theta1):.2f}, θ2 = {np.degrees(theta2):.2f}, θ3 = {np.degrees(theta3):.2f}")

    def IK_paper(self, global_x, global_y, global_z):
        x, y, z = ForwardKinematics.global_to_leg_frame(self.leg, global_x, global_y, global_z)  # local leg frame

        # Step 1: θ1 - coxa angle (rotation about Z)
        theta1 = np.arctan2(y, x)

        # Step 2: Project to sagittal plane
        r = np.sqrt(x**2 + y**2)
        x_ = r - cfg.l_coxa   # Effective forward reach
        z_ = z
        d = np.sqrt(x_**2 + z_**2)  # Distance from femur base to foot

        # Reachability clamp
        max_reach = cfg.l_femur + cfg.l_tibia + 5  # add 5mm buffer
        if d > max_reach:
            print(f"[{self.leg}] Unreachable pose! d = {d:.2f}, Max = {max_reach:.2f}")

        # Step 3: Use law of cosines for θ3 (knee)
        alpha = np.arccos(self.clamp((cfg.l_femur**2 + cfg.l_tibia**2 - d**2) / (2 * cfg.l_femur * cfg.l_tibia), -1, 1))
        theta3 = np.pi - alpha

        # Step 4: Use law of cosines + atan2 for θ2 (hip)
        beta = np.arccos(self.clamp((cfg.l_femur**2 + d**2 - cfg.l_tibia**2) / (2 * cfg.l_femur * d), -1, 1))
        gamma = np.arctan2(z_, x_)
        theta2 = beta - gamma

        # Step 5: Convert to degrees and clamp to servo limits
        self.coxa_deg = self.clamp(np.degrees(theta1), min_angle, max_angle)
        self.femur_deg = self.clamp(np.degrees(theta2), min_angle, max_angle)
        self.tibia_deg = self.clamp(np.degrees(theta3), min_angle, max_angle)

        # Debug info
        print(f"[{self.leg}] x={x:.2f}, y={y:.2f}, z={z:.2f}, r={r:.2f}, x_={x_:.2f}, z_={z_:.2f}, d={d:.2f}")
        print(f"θ1 = {np.degrees(theta1):.2f}, θ2 = {np.degrees(theta2):.2f}, θ3 = {np.degrees(theta3):.2f}")
