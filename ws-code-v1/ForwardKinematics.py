import numpy as np
from leg_config import Config as cfg

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

# def forward_kinematics(theta1, theta2, theta3):
#     '''
#     Compute 3-DOF leg forward kinematics using standard D-H convention.
#     return 4x4 transformation matrix from base to foot
#     '''
#     # D-H parameters: [θ, d, a(i-1), α(i-1)]
#     dh_params = [
#         [theta1, 0, 0,      -np.pi/2],        # i = 1 Coxa joint
#         [theta2, 0, cfg.l_coxa,  0],        # i = 2 Femur joint
#         [-theta3, 0, cfg.l_femur, 0],        # i = 3 Tibia joint
#         [0,      0, cfg.l_tibia, 0]         # i = 4 Foot tip (just extension)
#     ]

#     # this is the process to get the transformation matrix from coxa to foot tip
#     T = np.identity(4)
#     for theta, d, a, alpha in dh_params:
#         T = T @ standard_dh_transform(theta, d, a, alpha)

#     return T

def forward_kinematics_gemini(theta1, theta2, theta3):
    '''
    Compute 3-DOF leg forward kinematics using standard D-H convention.
    Returns the 4x4 transformation matrix from the coxa joint frame to the foot tip frame.
    '''
    # Standard D-H parameters for a 3-DOF leg: [theta_i, d_i, a_i, alpha_i]
    # This represents the transformation from one joint frame to the next.
    dh_params = [
        # i=1: Coxa joint. Transforms from base (frame 0) to femur joint (frame 1).
        # alpha=-90deg rotates the XY plane to the vertical XZ plane for the leg.
        [theta1, 0, cfg.l_coxa, -np.pi/2],

        # i=2: Femur joint. Transforms from femur joint (frame 1) to tibia joint (frame 2).
        [theta2, 0, cfg.l_femur, 0],
        
        # i=3: Tibia joint. Transforms from tibia joint (frame 2) to foot tip (frame 3).
        [-theta3, 0, cfg.l_tibia, 0]
    ]

    T_coxa_to_foot = np.identity(4)
    for theta, d, a, alpha in dh_params:
        T_coxa_to_foot = T_coxa_to_foot @ standard_dh_transform(theta, d, a, alpha)

    return T_coxa_to_foot

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
    joint_angles_rad = deg2rad_joint_angles(cfg.joint_angles_deg)

    for leg in joint_angles_rad.keys():
        theta1, theta2, theta3 = joint_angles_rad[leg]
        x, y, z = cfg.leg_coxa_pos[leg]
        yaw = cfg.leg_yaw[leg]

        T_origin_to_coxa = base_transform(x, y, z, yaw)
        T_coxa_to_foot = forward_kinematics_gemini(theta1, theta2, theta3)
        T_origin_to_foot = T_origin_to_coxa @ T_coxa_to_foot

        foot_position_from_origin[leg] = T_origin_to_foot[0:3, 3]
    
    return foot_position_from_origin

def global_to_leg_frame(leg_name, global_x, global_y, global_z):
    x, y, z = cfg.leg_coxa_pos[leg_name]
    yaw = cfg.leg_yaw[leg_name]

    # Transformation matrix: base to coxa
    T_base_to_coxa = base_transform(x, y, z, yaw)
    # print("T_base_to_coxa:\n", np.array2string(T_base_to_coxa, formatter={'float_kind':lambda x: f"{x:.2f}"}))

    T_coxa_to_base = np.linalg.inv(T_base_to_coxa)
    # print("T_coxa_to_base:\n", np.array2string(T_coxa_to_base, formatter={'float_kind':lambda x: f"{x:.2f}"}))

    foot_global_homog = np.array([global_x, global_y, global_z, 1])
    # print("foot_global_homog =\n", np.array2string(foot_global_homog, formatter={'float_kind':lambda x: f"{x:.2f}"}))
    
    foot_local = T_coxa_to_base @ foot_global_homog
    lx, ly, lz = foot_local[:3]

    print(f"[{leg_name}], local_x = {lx:.2f}, local_y = {ly:.2f}, local_z = {lz:.2f}")
    return np.array([lx, ly, lz])

##############################################################

# foot_positions = compute_foot_position_from_origin()
# for leg, pos in foot_positions.items():
#     print(f"{leg} foot position from origin: x = {pos[0]:.2f} mm, y = {pos[1]:.2f} mm, z = {pos[2]:.2f} mm")