from TriLeg import Trileg

''' 
GWEN 2.0 Configuration:
     FRONT ↑ +Y
           |
      L1   |   R1
-X    L2   |   R2    -> +X
      L3   |   R3
           |
     BACK   -Y
+Z is vertical upward

Roll: rotation about front-back axis (X)
Pitch: rotation about left-right axis (Y)
Yaw: rotation about vertical axis (Z)
'''

class Spider:
    def _init__(self):
        self.L1 = Trileg('L1', 
                         sc= 0, sf= 1, st= 2, 
                         coxa_deg= 0, femur_deg= 0, tibia_deg= 0)
        self.L2 = Trileg('L2', 
                         sc= 3, sf= 4, st= 5, 
                         coxa_deg= 0, femur_deg= 0, tibia_deg= 0)
        self.L3 = Trileg('L3', 
                         sc= 6, sf= 7, st= 8, 
                         coxa_deg= 0, femur_deg= 0, tibia_deg= 0)
        self.R1 = Trileg('R1', 
                         sc= 21, sf= 22, st= 23, 
                         coxa_deg= 0, femur_deg= 0, tibia_deg= 0)
        self.R2 = Trileg('R2', 
                         sc= 18, sf= 19, st= 20, 
                         coxa_deg= 0, femur_deg= 0, tibia_deg= 0)
        self.R3 = Trileg('R3', 
                         sc= 9, sf= 10, st= 11, 
                         coxa_deg= 0, femur_deg= 0, tibia_deg= 0)
        
    ''' gait motion code here '''