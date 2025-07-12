from ForwardKinematics import compute_foot_position_from_origin
from Spider import Spider
from leg_config import Config as cfg

# Set test joint angles (deg)
cfg.joint_angles_deg = {
    'L1': [0, -25, -60],
    'L2': [15, 30, 10],
    'L3': [-24, 22, 60],
    'R1': [30, 25, 0],
    'R2': [-20, -30, 0],
    'R3': [30, 20, 10],
}

# Run FK
foot_positions = compute_foot_position_from_origin()

# Instantiate the robot
gwen = Spider()

print("===== FK → IK Validation =====")
for leg in ['L1', 'L2', 'L3', 'R1', 'R2', 'R3']:
    x, y, z = foot_positions[leg]
    print(f"\n{leg} FK Foot Position: x = {x:.2f}, y = {y:.2f}, z = {z:.2f}")

    # Perform IK
    getattr(gwen, leg).IK(x, y, z)

    # Print results
    print(f"{leg} Original Angles (deg): {cfg.joint_angles_deg[leg]}")
    print(f"{leg} IK Angles (deg): {getattr(gwen, leg).coxa_deg:.2f}, {getattr(gwen, leg).femur_deg:.2f}, {getattr(gwen, leg).tibia_deg:.2f}")
