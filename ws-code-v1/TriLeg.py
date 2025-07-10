import maestro
from leg_config import Config as cfg
import numpy as np
import ForwardKinematics

ServoController = maestro.Controller('/dev/ttyAMA0')

min_angle = ServoController.getMin(0)
print(f"servo minimum range: {min_angle}")
max_angle = ServoController.getMax(0)
print(f"servo maximum range: {max_angle}")

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
        self.coxa_deg = int((100 * self.coxa_deg)/3 + 6000)
        self.femur_deg = int((100 * self.femur_deg)/3 + 6000)
        self.tibia_deg = int((100 * self.tibia_deg)/3 + 2000)
        print(f"coxa {self.leg}: {self.coxa_deg}")
        print(f"femur {self.leg}: {self.femur_deg}")
        print(f"tibia {self.leg}: {self.tibia_deg}")
    
    def move(self):
        self.angleToDC()
        ServoController.setTarget(self.sc, self.coxa_deg)
        ServoController.setTarget(self.sf, self.femur_deg)
        ServoController.setTarget(self.st, self.tibia_deg)

    def clean(self):
        ServoController.setTarget(self.sc, 0)
        ServoController.setTarget(self.sf, 0)
        ServoController.setTarget(self.st, 0)

    def clamp(self, x, min_val, max_val):
        return max(min_val, min(x, max_val))

    def IK(self, foot_target):
        local_pos = ForwardKinematics.global_to_leg_frame(self.leg, foot_target)
        x, y, z = local_pos

        # Step 1: Coxa angle
        theta1 = np.arctan2(y, x)

        # Step 2: Projection into sagittal plane
        r = np.sqrt(x**2 + y**2)
        x_ = r - cfg.l_coxa
        z_ = z
        d = np.sqrt(x_**2 + z_**2)

        # Step 3: Check reachability
        d = self.clamp(d, 1e-6, cfg.l_femur + cfg.l_tibia - 1e-6)

        # Step 4: Compute angles using Law of Cosines
        theta3 = np.pi - np.arccos(self.clamp((cfg.l_femur**2 + cfg.l_tibia**2 - d**2) / (2 * cfg.l_femur * cfg.l_tibia), -1, 1))
        alpha = np.arccos(self.clamp((cfg.l_femur**2 + d**2 - cfg.l_tibia**2) / (2 * cfg.l_femur * d), -1, 1))
        beta = np.arctan2(z_, x_)
        theta2 = beta + alpha

        # Set degrees (you can round here if needed)
        self.coxa_deg = self.clamp(np.degrees(theta1), min_angle, max_angle)
        self.femur_deg = self.clamp(np.degrees(theta2), min_angle, max_angle)
        self.tibia_deg = self.clamp(np.degrees(theta3), min_angle, max_angle)

        print(f"[{self.leg}] IK: θ1 = {self.coxa_deg:.2f}°, θ2 = {self.femur_deg:.2f}°, θ3 = {self.tibia_deg:.2f}°")

