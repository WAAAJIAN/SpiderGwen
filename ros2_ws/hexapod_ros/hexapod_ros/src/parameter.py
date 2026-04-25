## parameter.py
## Shared configuration and helper functions for SpiderGwen RPi motion planner.
## Used by legstate.py and spider.py.
##
## Note: servo IDs, joint angle ranges, and DH table have been removed —
## those are ESP32-only concerns now (see leg_kinematics_config.h).
 
from math import *
import numpy as np

# ===== Helper functions =====

def vectorMull(m1, m2):
    """2x2 matrix × 2-vector multiplication."""
    return [
        m1[0][0] * m2[0] + m1[0][1] * m2[1],
        m1[1][0] * m2[0] + m1[1][1] * m2[1]
    ]

def polarVector(angle, value=1):
    return [value * cos(radians(angle)), value * sin(radians(angle))]

def transformLegtoBody(leg, vector, reverse=False):
    """Transform a leg-local [x, y] vector into body frame."""
    return vectorMull(transformMat[leg], vector)

# ===== Physical constants =====

g = 9.80665  # m/s²

# ===== Leg geometry =====
# These are used by the RPi-side balance/walk trajectory math (legstate.py).
# The same values must match leg_kinematics_config.h on the ESP32.

ctc = (71.77, 90.31)  # coxa-to-body centre distances for corner and middle legs
                       # TODO: verify against actual hardware measurements

cl = 55.65   # coxa  length (mm)
fl = 110.0   # femur length (mm)
tl = 145.4   # tibia length (mm)

x_offset = 0      # lateral foot offset from leg base (mm)
y_offset = 312    # forward foot reach from coxa (mm)
z_offset = 0      # vertical foot offset from body plane (mm)

offset_angle = 54  # leg mounting angle from body Y-axis (degrees)
                   # TODO: verify against actual hardware

'''
Leg layout (top view):

        0 (0,0)   1 (1,0)
            \     /
             \   /
5 (0,1)-------+-------2 (1,1)
             /   \
            /     \
        4 (0,2)   3 (1,2)
'''

offset_angle_map = {
    0: offset_angle + 90,
    1: offset_angle,
    2: 0,
    5: 180,
    3: -offset_angle,
    4: offset_angle + 180
}

leg_type_map = {
    0: 1,  # corner
    1: 1,  # corner
    2: 0,  # middle
    3: 1,  # corner
    4: 1,  # corner
    5: 0   # middle
}

# Per-leg coordinate transform matrices (leg frame → body frame)
M0 = [[-cos(radians(offset_angle)), -sin(radians(offset_angle))],
      [-sin(radians(offset_angle)),  cos(radians(offset_angle))]]
M1 = [[ cos(radians(offset_angle)),  sin(radians(offset_angle))],
      [-sin(radians(offset_angle)),  cos(radians(offset_angle))]]
M2 = [[1, 0], [0, 1]]
M3 = [[ cos(radians(offset_angle)), -sin(radians(offset_angle))],
      [ sin(radians(offset_angle)),  cos(radians(offset_angle))]]
M4 = [[-cos(radians(offset_angle)),  sin(radians(offset_angle))],
      [ sin(radians(offset_angle)),  cos(radians(offset_angle))]]
M5 = [[-1, 0], [0, 1]]

transformMat = {0: M0, 1: M1, 2: M2, 3: M3, 4: M4, 5: M5}

# Rotation correction vectors for roll/pitch/yaw balance
# Returns (roll_vec, pitch_vec, yaw_vec) each as (dx, dy, dz)
R = lambda x, offset, roll=0, pitch=0, yaw=0, loc=[0, 0]: (
    (0,
     ctc[x] * cos(radians(offset)) * (1 - cos(radians(roll))),
     ctc[x] * cos(radians(offset)) * sin(radians(roll))),
    (ctc[x] * sin(radians(offset)) * (1 - cos(radians(pitch))),
     0,
     ctc[x] * sin(radians(offset)) * sin(radians(pitch))),
    ((ctc[x] + sqrt(loc[0]**2 + loc[1]**2)) * sin(radians(yaw)),
     (ctc[x] + sqrt(loc[0]**2 + loc[1]**2)) * cos(radians(yaw)) - (ctc[x] + loc[1]),
     0)
)

# ===== Gait parameters =====

period   = 30000  # gait cycle period (arbitrary time units)
sampling = 40     # number of slices per cycle (controls leg speed)

gait = {
    0: "tripod",
    1: "wave",
    2: "ripple",
    3: "bipod",
    4: "tetra"
}

gait_params = {
    "tripod": {
        "time_on_air":    0.5,
        "phase_offsets":  [0.0, 0.5, 0.0, 0.5, 0.0, 0.5],
        "stop_time":      5
    },
    "wave": {
        "time_on_air":    1/6,
        "phase_offsets":  [0.0, 5/6, 4/6, 3/6, 2/6, 1/6]
    },
    "ripple": {
        "time_on_air":    0.5,
        "phase_offsets":  [0.0, 5/6, 3/6, 1/6, 4/6, 2/6]
    },
    "bipod": {
        "time_on_air":    1/3,
        "phase_offsets":  [2/3, 1/3, 0.0, 2/3, 1/3, 0.0]
    },
    "tetra": {
        "time_on_air":    1/3,
        "phase_offsets":  [0.0, 1/3, 2/3, 0.0, 2/3, 1/3]
    }
}

walk_distance = 60  # max foot displacement per step (mm)

# ===== Teleop direction mapping =====

direction = {
    'w': [1,  0],
    's': [-1, 0],
    'a': [0, -1],
    'd': [0,  1],
    'q': polarVector(315),
    'e': polarVector(45),
    'z': polarVector(225),
    'x': polarVector(135),
    'o': [1,  0, 1],   # rotate clockwise
    'p': [-1, 0, 1]    # rotate counter-clockwise
}