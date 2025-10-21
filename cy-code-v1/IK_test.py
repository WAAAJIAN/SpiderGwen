import numpy as np
from math import sin, cos, radians, sqrt, asin, acos, atan2, degrees
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import traceback
from parameter import *

# ---- simple parameters (adjust if needed) ----
cl = 55.65   # coxa length (mm)
fl = 110    # femur length (mm)
tl = 155   # tibia length (mm)

# joint limits (deg)
coxa_limits = (-60, 60)
femur_limits = (-60, 60)
tibia_limits = (0, 120)

# trajectory settings
direction = [0, 1]   # forward vector [side, forward]
distance = 60    # stride amplitude
z_offset = 150         # set 0 so coordinates are relative to coxa for IK debugging
x_offset = 0
y_offset = 180

# sampling
phases = np.linspace(0, 360, 181)  # 2° step

def IK(x, y, z):
    """IK expects (x lateral, y forward, z vertical) in coxa frame.
       Returns tuple (ok, (a,b,c)) where a=coxa deg, b=femur deg, c=tibia deg."""
    try:
        r = sqrt(x**2 + y**2) - cl
        k = sqrt(r**2 + z**2)
        if k < 1e-6:
            raise ValueError("Target too close to femur pivot.")
        if k > fl + tl or k < abs(fl - tl):
            raise ValueError("Target out of reachable workspace.")
        theta = asin(max(-1.0, min(1.0, z / k)))
        theta2 = acos(max(-1.0, min(1.0, ((fl**2) + (k**2) - (tl**2)) / (2 * fl * k))))
        a = degrees(atan2(x, y))                   # coxa
        b = degrees(theta2 - theta)                # femur
        c = 180.0 - degrees(acos(max(-1.0, min(1.0, ((fl**2) + (tl**2) - (k**2)) / (2 * fl * tl)))))
        # limit checks
        if not (coxa_limits[0] <= a <= coxa_limits[1]):
            raise ValueError("coxa out")
        if not (femur_limits[0] <= b <= femur_limits[1]):
            raise ValueError("femur out")
        if not (tibia_limits[0] <= c <= tibia_limits[1]):
            raise ValueError("tibia out")
        return True, (a, b, c)
    except Exception:
        # return False and the traceback for inspection if desired
        return False, traceback.format_exc()

# generate commanded foot positions (same logic as your calculateWalk)
cmd_positions = []
ik_ok = []
ik_angles = []

leg = 1
type_ = 1
for ph in phases:
    if ph <= 180:
        turn_distance = 1.0 * distance
        turn_distance = walk_cycle["on_air"][type_] * distance
        x = direction[1] * turn_distance * (cos(radians(ph)) * -0.5 + 0.5) - (distance if type_ > 0 else 0)
        y = -direction[0] * turn_distance * (cos(radians(ph)) * -0.5 + 0.5)
        z = - distance * sin(radians(ph)) + z_offset
    else:
        turn_distance = walk_cycle["on_ground"][type_] * distance
        x = direction[1] * turn_distance * (cos(radians(ph)) * -0.5 + 0.5) - (distance if type_ < 2 else 0)
        y = -direction[0] * turn_distance * (cos(radians(ph)) * -0.5 + 0.5)
        z = z_offset
    new_vec = transformBodyCoortoLeg(leg, [x,y])
    # apply (simple) transform: here we keep leg frame == coxa frame (no rotation)
    X = x_offset + new_vec[0]
    Y = y_offset + new_vec[1]
    Z = z
    cmd_positions.append((X, Y, Z))

    ok, info = IK(X, Y, Z)
    ik_ok.append(ok)
    ik_angles.append(info)

# convert lists to arrays
cmd_positions = np.array(cmd_positions)
xs, ys, zs = cmd_positions[:,0], cmd_positions[:,1], cmd_positions[:,2]
ok_mask = np.array(ik_ok, dtype=bool)

# plot results
fig = plt.figure(figsize=(9,7))
ax = fig.add_subplot(111, projection='3d')
# commanded trajectory line
ax.plot(xs, ys, zs, color='blue', alpha=0.6, label='commanded traj')
# points: IK-ok green, IK-fail red
ax.scatter(xs[ok_mask], ys[ok_mask], zs[ok_mask], color='green', s=20, label='IK OK')
ax.scatter(xs[~ok_mask], ys[~ok_mask], zs[~ok_mask], color='red', s=20, label='IK FAIL')

ax.set_xlabel('Lateral X (mm)')
ax.set_ylabel('Forward Y (mm)')
ax.set_zlabel('Z (mm)')
ax.set_title('Walk trajectory and IK result')
ax.legend()
plt.show()

# print out failures for inspection
fails = [(phases[i], cmd_positions[i], ik_angles[i]) for i in range(len(phases)) if not ik_ok[i]]
print(f"Total points: {len(phases)}, IK OK: {ok_mask.sum()}, FAIL: {len(fails)}")
if fails:
    print("Sample failures (phase, pos, trace):")
    for f in fails[:6]:
        print(f)