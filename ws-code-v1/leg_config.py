import numpy as np

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

class Config:
    l_coxa = 76.42
    l_femur = 60.00
    l_tibia = 157.21

    # tibia angle can only be +ve !!!!!
    joint_angles_deg = {
        'L1': [0, 1, 0],
        'L2': [30, -40, 50],
        'L3': [22, 0, 60],
        'R1': [30, 25, 0],
        'R2': [-20, -30, 0],
        'R3': [30, 20, 30],
    }

    leg_coxa_pos = {
        'L1': [-53.2,   73.09,  0],
        'L2': [-71.77,  0,      0],
        'L3': [-53.2,  -73.09,  0],
        'R1': [53.2,    73.09,  0],
        'R2': [71.77,   0,      0],
        'R3': [53.2,   -73.09,  0]
    }

    leg_yaw = {
        'L1': np.pi*0.75,
        'L2': np.pi,
        'L3': np.pi*-0.75,
        'R1': np.pi*0.25,
        'R2': 0,
        'R3': np.pi*-0.25,
    }
