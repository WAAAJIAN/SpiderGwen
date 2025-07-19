from ForwardKinematics import compute_foot_position_from_origin
from Spider import Spider
from leg_config import Config as cfg

# Run FK
foot_positions = compute_foot_position_from_origin()

# Instantiate the robot
gwen = Spider()

print("===== FK → IK Validation =====")
for leg in ['L1', 'L2', 'L3', 'R1', 'R2', 'R3']:
# for leg in ['L3']:
    x, y, z = foot_positions[leg]
    print(f"\n{leg} FK Foot Position: x = {x:.2f}, y = {y:.2f}, z = {z:.2f}")

    getattr(gwen, leg).IK(x, y, z)

    print(f"{leg} IK Angles (deg): {getattr(gwen, leg).coxa_deg:.2f}, {getattr(gwen, leg).femur_deg:.2f}, {getattr(gwen, leg).tibia_deg:.2f}")
