import maestro
import numpy as np

ServoController = maestro.Controller('/dev/ttyAMA0')

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

l_coxa = 76.42  # in mm
l_femur = 60.00  # in mm
l_tibia = 157.21  #  in mm

# anticlockwise is +ve
joint_angles_deg = {
        'L1': [0, 0, 0],
        'L2': [0, 0, 0],
        'L3': [0, 0, 0],
        'R1': [0, 0, 0],
        'R2': [0, 0, 0],
        'R3': [0, 0, 0],
    }

# where the coxa is relative to the body center/origin, [x, y, z] in mm
leg_coxa_pos = {
    'L1': [-53.2,   73.09,  0],
    'L2': [-71.77,  0,      0],
    'L3': [-53.2,  -73.09,  0],
    'R1': [53.2,    73.09,  0],
    'R2': [71.77,   0,      0],
    'R3': [53.2,   -73.09,  0]
}

# yaw angles for each leg, in radians
leg_yaw = {
    'L1': np.pi*0.75,      
    'L2': np.pi,      
    'L3': np.pi*-0.75,      
    'R1': np.pi*0.25,          
    'R2': 0,          
    'R3': np.pi*-0.25,          
}

def deg2rad_joint_angles(joint_angles_deg):
    joint_angles_rad = {}
    for leg, angles in joint_angles_deg.items():
        joint_angles_rad[leg] = [np.deg2rad(angle) for angle in angles]
    return joint_angles_rad

def standard_dh_transform(theta, d, a, alpha):
    ''' 
    Standard Denavit-Hartenberg convention is used for this 3-DOF leg kinematics. Symbol meaning:
        - θ: Joint angle (rotation about Z-axis)
        - d: Link offset (translation along Z-axis)
        - a: Link length (translation along X-axis)
        - α: Link twist (rotation about X-axis)
    Using this convention instead of the modified D-H convention is more straightforward for this 3-DOF leg, 
    defining the leg as a 3-link structure with a fixed base and a foot at the end.
    '''
    ct = np.cos(theta)
    st = np.sin(theta)
    calpha = np.cos(alpha)
    salpha = np.sin(alpha) 
    
    dh_transform_matrix = np.array([
        [ct, -st * calpha, st * salpha,   a * ct],
        [st, ct * calpha,  -ct * salpha,  a * st],
        [0,  salpha,       calpha,        d],
        [0,  0,            0,             1]
    ])

    return dh_transform_matrix

def forward_kinematics(theta1, theta2, theta3):
    '''
    Compute 3-DOF leg forward kinematics using standard D-H convention.
    return 4x4 transformation matrix from base to foot
    '''
    # D-H parameters: [θ, d, a(i-1), α(i-1)]
    dh_params = [
        [theta1, 0, 0,      -np.pi/2],        # i = 1 Coxa joint
        [theta2, 0, l_coxa,  0],        # i = 2 Femur joint
        [theta3, 0, l_femur, 0],        # i = 3 Tibia joint
        [0,      0, l_tibia, 0]         # i = 4 Foot tip (just extension)
    ]

    # this is the process to get the transformation matrix from coxa to foot tip
    T = np.identity(4)
    for theta, d, a, alpha in dh_params:
        T = T @ standard_dh_transform(theta, d, a, alpha)

    return T

def base_transform(x, y, z, yaw):
    '''
    Return transformation matrix for leg's coxa position to body center/origin and orientation (rotation about Z).
    '''
    cyaw = np.cos(yaw)
    syaw = np.sin(yaw)

    base_transform_matrix = np.array([
        [cyaw, -syaw, 0, x],
        [syaw,  cyaw, 0, y],
        [0,     0,    1, z],
        [0,     0,    0, 1]
    ])

    return base_transform_matrix

def compute_foot_position_from_origin():
    '''
    Compute the foot position from the origin (body center) for each leg.
    '''
    foot_position_from_origin = {}
    joint_angles_rad = deg2rad_joint_angles(joint_angles_deg)

    for leg in joint_angles_rad.keys():
        theta1, theta2, theta3 = joint_angles_rad[leg]
        x, y, z = leg_coxa_pos[leg]
        yaw = leg_yaw[leg]

        T_origin_to_coxa = base_transform(x, y, z, yaw)
        T_coxa_to_foot = forward_kinematics(theta1, theta2, theta3)
        T_origin_to_foot = T_origin_to_coxa @ T_coxa_to_foot

        foot_position_from_origin[leg] = T_origin_to_foot[0:3, 3]

    return foot_position_from_origin

foot_positions = compute_foot_position_from_origin()
for leg, pos in foot_positions.items():
    print(f"{leg} foot position from origin: x = {pos[0]:.2f} mm, y = {pos[1]:.2f} mm, z = {pos[2]:.2f} mm")

class Trileg:
    def __init__(self, leg, sc, sf, st):
        self.leg = leg # name of the leg (e.g., 'L1', 'L2', 'L3, 'R1', 'R2', 'R3')
        self.sc = sc # servo pin for coxa
        self.sf = sf # servo pin for femur
        self.st = st # servo pin for tibia

    