from math import *
from time import sleep  

# ===== Leg =====
period = 30000   # period of a leg cycle 
steps = 1000   # speed of motion
sampling = 10 # for full cycle

coxa_range = (-60, 60)
femur_range = (-60, 60)
tibia_range = (30, 150)

switch = {
    2 : 17,
    3 : 27,
    4 : 22,
    5 : 10,
    0 : 9,
    1 : 11
}

# tested highest point (0, 206, -206)

x_offset = 0     # initial x position of leg (vertical axis)
y_offset = 150  # initial y position of leg (horizontal axis from the coxa)
z_offset = 150  # initial z position of leg (height of bot)

ctc = (71.77, 90.31)   # ctc[0] for middle legs, ctc[1] for corner legs
cl = 55.65 # length of coxa
fl = 110    # length of femur
tl = 145.4   # length of tibia

offset_angle = 54
offset_angle_map = {0: offset_angle + 90, 1: offset_angle, 
                    2: 0, 5: 180, 
                    3: offset_angle, 4: offset_angle + 180} # offset angle of each leg from y axis

#Matrix for transform coordinate on each leg 
M0 = [[-cos(radians(offset_angle)), -sin(radians(offset_angle))],[-sin(radians(offset_angle)), cos(radians(offset_angle))]]    # leg 0
M1 = [[cos(radians(offset_angle)), sin(radians(offset_angle))], [-sin(radians(offset_angle)), cos(radians(offset_angle))]]    # leg 1
M2 = [[1, 0], [0, 1]]                                                                 # leg 2
M3 = [[cos(radians(offset_angle)), -sin(radians(offset_angle))], [sin(radians(offset_angle)), cos(radians(offset_angle))]]    # leg 3
M4 = [[-cos(radians(offset_angle)), sin(radians(offset_angle))], [sin(radians(offset_angle)), cos(radians(offset_angle))]]  # leg 4
M5 = [[-1, 0], [0, 1]]                                                                # leg 5

transformMat = {
    0: M0, 
    1: M1, 
    2: M2, 
    3: M3, 
    4: M4, 
    5: M5
}

# ==== pid ====
pid = {
    "roll": {
        "kp" : 2.4,
        "ki" : 2.5,
        "kd" : 0,
        "filter_coe" : 0.93,
        "max_I" : 25
    },
    "pitch":{
        "kp" : 2.4,
        "ki" : 2.5,
        "kd" : 0,
        "filter_coe" : 0.93,
        "max_I" : 25
    }
}
dt = 0.05

# Rotation "Matrix"
R = lambda x, offset, roll=0, pitch=0 : (
    (0, ctc[x] * cos(radians(offset)) * (1 - cos(radians(roll))), ctc[x] * cos(radians(offset)) * sin(radians(roll))),
    (ctc[x] * sin(radians(offset)) * (1 - cos(radians(pitch))), 0 , ctc[x] * sin(radians(offset)) * sin(radians(pitch))),
    (0 , 0 , 0)) # (roll, pitch, yaw)

# ===== Gait =====
gait = {
    0: "tripod", 
    1: "wave", 
    2: "ripple", 
    3: "bipod", 
    4: "tetra"
}

gait_params = {
    "tripod": {
        "time_on_air": 0.5, 
        "phase_offsets": [0.0, 0.5, 0.0, 0.5, 0.0, 0.5],
        "stop_time" : 1 # per half cycle
    },
    "wave": {
        "time_on_air": 1/6, 
        "phase_offsets": [0.0, 5/6, 4/6, 3/6, 2/6, 1/6]
    },
    "ripple": {
        "time_on_air": 0.5,
        "phase_offsets": [0.0, 5/6, 3/6, 1/6, 4/6, 2/6]
    },
    "bipod": {
        "time_on_air": 1/3,
        "phase_offsets": [2/3, 1/3, 0.0, 2/3, 1/3, 0.0]
    },
    "tetra": {
        "time_on_air": 1/3,
        "phase_offsets": [0.0, 1/3, 2/3, 0.0, 2/3, 1/3]
    }
}

walk_cycle = {
    "on_air": [0.5, 1, 0.5],
    "on_ground": [2, 2, 0]
}

walk_offset = {
    0 : 0.5,
    1 : 0,
    2 : -0.5
}

walk_distance = 60

# ===== helper function =====
def vectorMull(m1, m2): # transform vector (Matrix Multiplication)
    m3 = [(m1[0][0])*(m2[0]) + (m1[0][1])*(m2[1]), (m1[1][0])*(m2[0]) + (m1[1][1])*(m2[1])]
    return m3

def polarVector(angle, value = 1):
    return [value * cos(radians(angle)), value * sin(radians(angle))]

def transformBodyCoortoLeg(leg, vector, reverse=False): # vector : [x,y]
    newVec = vectorMull(transformMat[leg], vector)
    return newVec
