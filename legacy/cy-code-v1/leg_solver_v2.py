
import numpy as np
import matplotlib.pyplot as plt
from math import *
import traceback
import csv
from mpl_toolkits.mplot3d import Axes3D 

# ---------------------- USER PARAMETERS ----------------------
# link lengths (mm)
cl = 55.65
fl = 60
tl = 155

# joint limits in degrees (relative to link axes)
coxa_limits = (-60, 60)
femur_limits = (-60, 60) 
tibia_limits = (60, 180) 

# sampling resolution
coxa_samples = 50
theta_samples = 181 # resolution for theta1 / theta2 sampling; higher -> smoother workspace

# plot options
show_inner_boundary = True
show_joint_axes = True
show_grid = True

# ----------------------------------------------------------------

# helper conversions
deg2rad = np.pi / 180.0
rad2deg = 180.0 / np.pi

# Convert femur/tibia internal-angle representation to the 2-link IK typical angles:
# We'll use the following kinematic conventions for a planar 2-link manipulator anchored at origin:
# - theta1 = angle of femur measured from +x axis (forward) counter-clockwise (standard math convention)
# - theta2 = angle between femur and tibia measured as the angle to rotate femur to align with tibia (so that
# the tibia absolute angle = theta1 + theta2). For a fully extended collinear leg pointing along +x, theta1=0, theta2=0,
# internal femur-tibia angle = 180.

# We need to map between: internal_knee_angle (I = internal angle between femur and tibia) and theta2 used in FK:
# internal_knee_angle = 180 - theta2 (in degrees) --> because theta2 is the external rotation from femur to tibia.
# So theta2 = 180 - I

# Create theta1 and internal knee angle grids according to limits, then compute reachable (x,y)
# We'll parameterize femur pitch theta1 within femur_limits, and internal knee angle I within tibia_limits.

coxa_min, coxa_max = coxa_limits
femur_min, femur_max = femur_limits
tibia_min, tibia_max = tibia_limits

coxa_vals = np.linspace(coxa_min * deg2rad, coxa_max * deg2rad, coxa_samples)
femur_vals = np.linspace(femur_min * deg2rad, femur_max * deg2rad, theta_samples)
tibia_vals = np.linspace(tibia_min * deg2rad, tibia_max * deg2rad, theta_samples)
theta2_vals = (np.pi - tibia_vals)

# create meshgrid of joint parameters (careful with memory - use outer loops if too big). We'll generate reachable points
# by sweeping theta1 and I

# Pre-allocate lists to gather reachable points
Xs = []
Ys = []
Zs = []
tested_Xs = []
tested_Ys = []
tested_Zs = []
# tested_points = []
# rejected_points = []

def IK(x, y, z):
    try:
        # x: lateral (coxa axis), y: forward (along femur plane), z: vertical
        r = sqrt(x**2 + y**2) - cl            # distance from femur pivot
        k = sqrt(r**2 + z**2)
        if k < 1e-6:
            raise ValueError("Target too close to femur pivot.")
        if k > fl + tl or k < abs(fl - tl):
            raise ValueError("Target out of reachable workspace.")

        theta = asin(max(-1.0, min(1.0, z / k)))
        theta2 = acos(max(-1.0, min(1.0, ((fl**2) + (k**2) - (tl**2)) / (2 * fl * k))))

        a = degrees(atan2(x, y))             # coxa angle: atan2(lateral, forward)
        b = degrees(theta2 - theta)          # femur angle
        c = 180.0 - degrees(acos(max(-1.0, min(1.0, ((fl**2) + (tl**2) - (k**2)) / (2 * fl * tl)))))

        if a < coxa_min or a > coxa_max or b < femur_min or b > femur_max or c < tibia_min or c > tibia_max:
            raise ValueError("Angle exceeded.")
        return True
    except Exception:
        return False

# ...existing code...
for gamma in coxa_vals:
    for th in femur_vals:
        tibia_abs = th + theta2_vals
        y_line = fl * np.cos(th) + tl * np.cos(tibia_abs)
        z_line = fl * np.sin(th) + tl * np.sin(tibia_abs)

        yp = cl + y_line
        X = yp * np.cos(gamma)
        Y = yp * np.sin(gamma)
        Z = z_line

        Xs.append(X)
        Ys.append(Y)
        Zs.append(Z)

        # test each sampled point using coxa-frame coords: lateral=0, forward=cl + y_line[i], z=z_line[i]
        # for i in range(len(y_line)):
        #     if IK(0.0, cl + y_line[i], z_line[i]):
        #         tested_Xs.append(X[i])
        #         tested_Ys.append(Y[i])
        #         tested_Zs.append(Z[i])

# flatten lists of arrays to single 1D arrays for plotting
Xs = np.concatenate(Xs)
Ys = np.concatenate(Ys)
Zs = np.concatenate(Zs)

# tested lists are flat (appended scalars) so convert to numpy arrays if non-empty
if tested_Xs:
    tested_Xs = np.array(tested_Xs)
    tested_Ys = np.array(tested_Ys)
    tested_Zs = np.array(tested_Zs)
else:
    tested_Xs = np.array([])
    tested_Ys = np.array([])
    tested_Zs = np.array([])

# Compute convex hull / outer boundary if desired
# Simpler: compute distances and show scatter; then compute outer/inner radii for no-limits case

# Plot in 3D
fig = plt.figure(figsize=(10,8))
ax = fig.add_subplot(111, projection='3d')
ax.scatter(Xs, Ys, Zs, s=0.6, alpha=0.6)
if tested_Xs.size:
    ax.scatter(tested_Xs, tested_Ys, tested_Zs, color='red', s=1)

# draw body origin
ax.scatter([0], [0], [0], color='k', s=30)
ax.text(0, 0, 0, ' body origin', fontsize=8)

# optional: draw spherical outer/inner reach (visual aid)
u = np.linspace(0, 2*np.pi, 60)
v = np.linspace(0, np.pi, 30)
r_outer = fl + tl + cl
r_inner = abs(fl - tl) + cl
# draw only outer wireframe for reference
Xo = r_outer * np.outer(np.cos(u), np.sin(v))
Yo = r_outer * np.outer(np.sin(u), np.sin(v))
Zo = r_outer * np.outer(np.ones_like(u), np.cos(v))
ax.plot_wireframe(Xo, Yo, Zo, rstride=6, cstride=6, color='gray', alpha=0.15)

ax.set_xlabel('X (mm)')
ax.set_ylabel('Y (mm)')
ax.set_zlabel('Z (mm)')
ax.set_title(f'3D reachable workspace (cl={cl} mm, coxa range={coxa_min}..{coxa_max}°)')
plt.show()