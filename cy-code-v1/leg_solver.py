"""
2D Reachable Workspace Visualizer for a Two-Link Hexapod Leg

What it does:
- Plots the reachable workspace (all foot positions) for a planar 2-link leg (femur + tibia)
- Shows outer and inner workspace boundaries
- Optionally applies joint limits (in degrees) for femur and tibia
- Lets you click on the plot to show one IK solution (and draws the leg configuration)


At runtime you can edit the parameters at the top of the file (L1, L2, joint limits, resolution).
Click on any reachable point in the figure to display a sample leg pose (shows joint angles and reach).
"""

import numpy as np
import matplotlib.pyplot as plt
from math import *
import traceback
import csv

# ---------------------- USER PARAMETERS ----------------------
# link lengths (mm)
# L1 = 139.5 # femur length
# L2 = 180 # tibia length
# L2 = L1*1.4
L1 = 100
L2 = 130

# joint limits in degrees (relative to link axes)
# femur: rotation around hip pitch (measured from body-horizontal forward = 0 deg, positive down)
# tibia: internal femur-tibia angle (180 = straight). We'll param as tibia angle relative to femur, measured
# such that common "knee angle" = internal angle between femur and tibia.
# For sampling we will convert to joint angles used by 2-link IK (theta1, theta2)

femur_limits = (-60, 60) # degrees (relative pitch of the femur link)
tibia_limits = (50, 170) # internal femur-tibia angle in degrees (avoid 180 straight singularity)

# sampling resolution
theta_samples = 801 # resolution for theta1 / theta2 sampling; higher -> smoother workspace

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

femur_min, femur_max = femur_limits
I_min, I_max = tibia_limits

theta1_vals = np.linspace(femur_min * deg2rad, femur_max * deg2rad, theta_samples)
I_vals = np.linspace(I_min * deg2rad, I_max * deg2rad, theta_samples)

# create meshgrid of joint parameters (careful with memory - use outer loops if too big). We'll generate reachable points
# by sweeping theta1 and I

# Pre-allocate lists to gather reachable points
xs = []
ys = []
tested_xs = []
tested_ys = []
tested_points = []
rejected_points = []

def IK(y, z, f, t):
    try:
        k = sqrt((y**2)+(z**2))
        theta = asin(z/k)

        theta2 = acos(((L1**2)+(k**2)-(L2**2))/(2*L1*k))
        if y >= 0:
            b = degrees(theta2 - theta)
        else:
            b = degrees(-pi + theta + theta2)
        c = degrees(acos(((L1**2)+(L2**2)-(k**2))/(2*L1*L2)))
        if b > femur_max or b < femur_min or c > I_max or c < I_min:
            rejected_points.append((y, z, f, t, b, c, ""))
            return False
        tested_points.append((y, z, f, t, b, c))
        return True
    except Exception as e:
        # print("Math error:", e)
        tb_str = traceback.format_exc()
        rejected_points.append((y, z, f, t, -99, -99, tb_str))
        return False

for th in range(len(theta1_vals)):
    # For a given femur angle, the tibia absolute angle is theta_tibia = theta1 + theta2
    # where theta2 = 180deg - I (in degrees). Convert to radians.
    theta2_vals = (np.pi - I_vals) 
    # Compute absolute tibia angles
    tibia_abs = theta1_vals[th] + theta2_vals
    # FK: x = L1*cos(theta1_vals[th]) + L2*cos(tibia_abs)
    # y = L1*sin(theta1_vals[th]) + L2*sin(tibia_abs)
    x_line = L1 * np.cos(theta1_vals[th]) + L2 * np.cos(tibia_abs)
    y_line = L1 * np.sin(theta1_vals[th]) + L2 * np.sin(tibia_abs)

    xs.append(x_line)
    ys.append(y_line)

    fa = theta1_vals[th] * rad2deg
    for i in range(len(x_line)):
        ta = theta2_vals[th] * rad2deg
        if IK(x_line[i], y_line[i], fa, ta):
            tested_xs.append(x_line[i])
            tested_ys.append(y_line[i])
# try:
#     tested_xs = np.concatenate(tested_xs)
#     tested_ys = np.concatenate(tested_ys)
# except Exception as e:
#     print("e: ", e)
xs = np.concatenate(xs)
ys = np.concatenate(ys)

# Compute convex hull / outer boundary if desired
# Simpler: compute distances and show scatter; then compute outer/inner radii for no-limits case

# Plotting
fig, ax = plt.subplots(figsize=(8,8))
ax.set_aspect('equal', 'box')
ax.scatter(xs, ys, s=0.8, alpha=0.6)
ax.scatter(tested_xs, tested_ys, color='red', s=1)
ax.invert_yaxis()

# draw origin and hip
ax.plot(0, 0, 'ko', markersize=6)
ax.text(0, 0, ' hip (0,0)', fontsize=10)

# draw outer circle (max reach) and inner circle (min reach when folded)
max_reach = L1 + L2
min_reach = abs(L1 - L2)
outer = plt.Circle((0,0), max_reach, fill=False, linestyle='--')
ax.add_artist(outer)
if show_inner_boundary:
    inner = plt.Circle((0,0), min_reach, fill=False, linestyle=':')
    ax.add_artist(inner)

# with open('rejected_points.csv', 'w', newline='', encoding='utf-8') as csvfile:
#     writer = csv.writer(csvfile)
#     writer.writerow(['x', 'z', 'fa', 'ta', 'cfa', 'cta', 'traceback'])
#     writer.writerows(rejected_points)

# with open('tested_points.csv', 'w', newline='', encoding='utf-8') as csvfile:
#     writer = csv.writer(csvfile)
#     writer.writerow(['x', 'z', 'fa', 'ta', 'cfa', 'cta'])
#     writer.writerows(tested_points)

# Optionally show joint axes for a default neutral pose (middle of ranges)
if show_joint_axes:
    theta1_neutral = 0.5 * (femur_min + femur_max) * deg2rad
    I_neutral = 0.5 * (I_min + I_max) * deg2rad
    theta2_neutral = np.pi - I_neutral
    tibia_abs_neutral = theta1_neutral + theta2_neutral
    xk = [0, L1 * np.cos(theta1_neutral), L1 * np.cos(theta1_neutral) + L2 * np.cos(tibia_abs_neutral)]
    yk = [0, L1 * np.sin(theta1_neutral), L1 * np.sin(theta1_neutral) + L2 * np.sin(tibia_abs_neutral)]
    ax.plot(xk, yk, '-o', linewidth=2, markersize=6, label='neutral pose')
    ax.legend()

ax.set_xlabel('x (mm)')
ax.set_ylabel('z (mm)')
ax.set_title(f'Reachable workspace (L1={L1} mm, L2={L2} mm)')
ax.grid(show_grid)

# click handler to show IK solution for clicked point

def ik_two_link(x, y, L1, L2, elbow_up=True):
    # returns theta1, I_internal (degrees) for given target x,y if reachable. else None
    d = np.hypot(x, y)
    if d > (L1 + L2) + 1e-6 or d < abs(L1 - L2) - 1e-6:
        return None
    # Law of cosines for angle at knee (between femur and tibia external angle)
    # cos_phi = (L1^2 + L2^2 - d^2) / (2*L1*L2) where phi is internal angle? careful
    # Standard IK (theta2 external angle): cos_theta2 = (x^2+y^2 - L1^2 - L2^2)/(2*L1*L2)
    cos_theta2 = (d*d - L1*L1 - L2*L2) / (2*L1*L2)
    cos_theta2 = np.clip(cos_theta2, -1.0, 1.0)
    if elbow_up:
        theta2 = np.arccos(cos_theta2)
    else:
        theta2 = -np.arccos(cos_theta2)
    # theta1 = atan2(y,x) - atan2(L2*sin(theta2), L1 + L2*cos(theta2))
    k1 = L1 + L2 * np.cos(theta2)
    k2 = L2 * np.sin(theta2)
    theta1 = np.arctan2(y, x) - np.arctan2(k2, k1)
    # convert to internal knee angle I (deg): I = 180deg - theta2 (in deg)
    I_internal = 180.0 - (theta2 * rad2deg)
    return theta1, I_internal

def ik_cal(y, z, L1, L2):
    try:
        k = sqrt((y**2)+(z**2))
        theta = asin(z/k)

        theta2 = acos(((L1**2)+(k**2)-(L2**2))/(2*L1*k))
        if y >= 0:
            b = degrees(theta2 - theta)
        else:
            b = degrees(-pi + theta + theta2)
        c = degrees(acos(((L1**2)+(L2**2)-(k**2))/(2*L1*L2)))
        if b > femur_max or b < femur_min or c > I_max or c < I_min:
            return None
        return -b,c
    except Exception as e:
        return None

selected_point_artist = None
line_artist = None
text_artist = None
selected_point_artist_2 = None
line_artist_2 = None
text_artist_2 = None

def on_click(event):
    global selected_point_artist, line_artist, text_artist
    global selected_point_artist_2, line_artist_2, text_artist_2

    if event.inaxes != ax:
        return
    x = event.xdata
    y = event.ydata
    sol = ik_two_link(x, y, L1, L2, elbow_up=True)
    # sol2 = ik_cal(x, y, L1, L2)
    if sol is None:
        print(f'Point ({x:.1f}, {y:.1f}) unreachable')
        return
    # if sol2 is None:
    #     print(f'Point ({x:.1f}, {y:.1f}) failed to calculate')
    #     return
    theta1, I_internal = sol
    theta2 = np.pi - (I_internal * deg2rad)
    tibia_abs = theta1 + theta2
    xk = [0, L1 * np.cos(theta1), L1 * np.cos(theta1) + L2 * np.cos(tibia_abs)]
    yk = [0, L1 * np.sin(theta1), L1 * np.sin(theta1) + L2 * np.sin(tibia_abs)]
    # remove previous artists
    if selected_point_artist is not None:
        try:
            selected_point_artist.remove()
        except Exception:
            pass
    if line_artist is not None:
        try:
            line_artist.remove()
        except Exception:
            pass
    if text_artist is not None:
        try:
            text_artist.remove()
        except Exception:
            pass
    # IKtheta1, IKI_internal = sol2
    # IKtheta1 = IKtheta1 * deg2rad
    # IKtheta2 = np.pi - (IKI_internal * deg2rad)
    # IKtibia_abs = IKtheta1 + IKtheta2
    # IKxk = [0, L1 * np.cos(IKtheta1), L1 * np.cos(IKtheta1) + L2 * np.cos(IKtibia_abs)]
    # IKyk = [0, L1 * np.sin(IKtheta1), L1 * np.sin(IKtheta1) + L2 * np.sin(IKtibia_abs)]
    # if selected_point_artist_2 is not None:
    #     try:
    #         selected_point_artist_2.remove()
    #     except Exception:
    #         pass
    # if line_artist_2 is not None:
    #     try:
    #         line_artist_2.remove()
    #     except Exception:
    #         pass
    # if text_artist_2 is not None:
    #     try:
    #         text_artist_2.remove()
    #     except Exception:
    #         pass

    # selected_point_artist_2 = ax.plot(x, y, 'rx', markersize=8)[0]
    # line_artist_2 = ax.plot(IKxk, IKyk, '-o', color='yellow', linewidth=2, markersize=6)[0]
    # angle_text_2 = f"theta2={IKtheta1*rad2deg:.1f}° knee_internal2={IKI_internal:.1f}°"
    # text_artist_2 = ax.text(0.02, 0.95, angle_text_2, transform=ax.transAxes, va='top', bbox=dict(boxstyle='round', fc='w'))

    selected_point_artist = ax.plot(x, y, 'rx', markersize=8)[0]
    line_artist = ax.plot(xk, yk, '-o', color='green', linewidth=2, markersize=6)[0]
    angle_text = f"theta1={theta1*rad2deg:.1f}° knee_internal={I_internal:.1f}°"
    text_artist = ax.text(0.02, 0.98, angle_text, transform=ax.transAxes, va='top', bbox=dict(boxstyle='round', fc='w'))

    fig.canvas.draw()

fig.canvas.mpl_connect('button_press_event', on_click)
plt.show()