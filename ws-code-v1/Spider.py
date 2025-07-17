from TriLeg import Trileg
import time
from leg_config import Config as cfg

class Spider:
    def __init__(self):
        self.L1 = Trileg('L1', 
                         sc= 0, sf= 1, st= 2, 
                         coxa_deg= cfg.joint_angles_deg['L1'][0], 
                         femur_deg= cfg.joint_angles_deg['L1'][1], 
                         tibia_deg= cfg.joint_angles_deg['L1'][2])
        self.L2 = Trileg('L2', 
                         sc= 3, sf= 4, st= 5, 
                         coxa_deg= cfg.joint_angles_deg['L2'][0],
                         femur_deg= cfg.joint_angles_deg['L2'][1],
                         tibia_deg= cfg.joint_angles_deg['L2'][2])
        self.L3 = Trileg('L3', 
                         sc= 6, sf= 7, st= 8, 
                         coxa_deg= cfg.joint_angles_deg['L3'][0],
                         femur_deg= cfg.joint_angles_deg['L3'][1],
                         tibia_deg= cfg.joint_angles_deg['L3'][2])
        self.R1 = Trileg('R1', 
                         sc= 21, sf= 22, st= 23, 
                         coxa_deg= cfg.joint_angles_deg['R1'][0],
                         femur_deg= cfg.joint_angles_deg['R1'][1],
                         tibia_deg= cfg.joint_angles_deg['R1'][2])
        self.R2 = Trileg('R2', 
                         sc= 18, sf= 19, st= 20, 
                         coxa_deg= cfg.joint_angles_deg['R2'][0],
                         femur_deg= cfg.joint_angles_deg['R2'][1],
                         tibia_deg= cfg.joint_angles_deg['R2'][2])
        self.R3 = Trileg('R3', 
                         sc= 9, sf= 10, st= 11, 
                         coxa_deg= cfg.joint_angles_deg['R3'][0],
                         femur_deg= cfg.joint_angles_deg['R3'][1],
                         tibia_deg= cfg.joint_angles_deg['R3'][2])
        
    def move(self):
        self.L1.move()
        time.sleep(0.1)
        self.L2.move()
        time.sleep(0.1)
        self.L3.move()
        time.sleep(0.1)
        self.R1.move()
        time.sleep(0.1)
        self.R2.move()
        time.sleep(0.1)
        self.R3.move()
        time.sleep(5)
    
    def clean(self):
        self.L1.clean()
        self.L2.clean()
        self.L3.clean()
        self.R1.clean()
        self.R2.clean()
        self.R3.clean()
        
    ''' gait motion code here '''

def main():
    gwen = Spider()
    gwen.L1.IK(-260.83, 280.72, 0)
    # gwen.L2.IK(-365.40, 0, 0)
    # gwen.L3.IK(-260.83, -280.72, 0)
    # gwen.R1.IK(260.83, 280.72, 0)
    # gwen.R2.IK(365.40, 0, 0)
    # gwen.R3.IK(260.83, -280.72, 0)
    # gwen.move()
    time.sleep(3)
    # gwen.clean()

main()
