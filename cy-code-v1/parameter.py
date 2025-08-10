from math import *
from time import sleep  

period = 30000   # period of a leg cycle (its not time!)
x_offset = 0     # initial x position of leg (vertical axis)
y_offset = 130   # initial y position of leg (horizontal axis from the center)
z_offset = 120  # initial z position of leg (height of bot)
steps = 2000     # speed of motion

ctc = (91.37, 105.47) # ctc[0] for middle legs, ctc[1] for corner legs
cl = 76.42 # length of coxa
fl = 60    # length of femur
tl = 157.21   # length of tibia

step = 20 # for leg movement to target
delays = 0.020 # for leg movement in s

offset_angle = 54
offset_angle_map = {0: offset_angle + 90, 1: offset_angle, 
                    2: 180, 5: 0, 
                    3: offset_angle + 180, 4: -offset_angle} # offset angle of each leg from y axis

#leg_max_length = 358.44 # maximum y position that leg can go to

#Matrix for transform coordinate on each leg (first version)
# M0 = [[sin(radians(30)), cos(radians(30))], [sin(radians(60)), -cos(radians(60))]]    # leg 0
# M1 = [[sin(radians(30)), cos(radians(30))], [-sin(radians(60)), cos(radians(60))]]    # leg 1
# M2 = [[1, 0], [0, 1]]                                                                 # leg 2
# M3 = [[sin(radians(30)), -cos(radians(30))], [sin(radians(60)), cos(radians(60))]]    # leg 3
# M4 = [[sin(radians(30)), -cos(radians(30))], [-sin(radians(60)), -cos(radians(60))]]  # leg 4
# M5 = [[1, 0], [0, -1]]                                                                # leg 5
# transformMat = {0: M0, 1: M1, 2: M2, 3: M3, 4: M4, 5: M5}

#Matrix for transform coordinate on each leg (second version)
M0 = [[-cos(radians(offset_angle)), sin(radians(offset_angle))],[sin(radians(offset_angle)), cos(radians(offset_angle))]]    # leg 0
M1 = [[cos(radians(offset_angle)), -sin(radians(offset_angle))], [sin(radians(offset_angle)), cos(radians(offset_angle))]]    # leg 1
M2 = [[1, 0], [0, 1]]                                                                 # leg 2
M3 = [[cos(radians(offset_angle)), sin(radians(offset_angle))], [-sin(radians(offset_angle)), cos(radians(offset_angle))]]    # leg 3
M4 = [[-cos(radians(offset_angle)), -sin(radians(offset_angle))], [-sin(radians(offset_angle)), cos(radians(offset_angle))]]  # leg 4
M5 = [[-1, 0], [0, 1]]                                                                # leg 5
transformMat = {0: M0, 1: M1, 2: M2, 3: M3, 4: M4, 5: M5}

# ==== pid ====
kp = 3
ki = 0 
kd = 0
dt = 0.01
filtercoe = 0.93

pitch = 0
roll = 0

# Rotation "Matrix"
R = lambda x, offset, roll=0, pitch=0 : (
    (0, ctc[x] * cos(radians(offset)) * (1 - cos(radians(roll))), ctc[x] * cos(radians(offset)) * sin(radians(roll))),
    (ctc[x] * sin(radians(offset)) * (1 - cos(radians(pitch))), 0 , ctc[x] * sin(radians(offset)) * sin(radians(pitch))),
    (0 , 0 , 0)) # (roll, pitch, yaw)

# ===== helper function =====
def vectorMull(m1, m2): # transform vector (Matrix Multiplication)
    m3 = [(m1[0][0])*(m2[0]) + (m1[0][1])*(m2[1]), (m1[1][0])*(m2[0]) + (m1[1][1])*(m2[1])]
    return m3

def polarVector(angle, value = 1):
    return [value * cos(radians(angle)), value * sin(radians(angle))]

def transformBodyCoortoLeg(leg, vector, reverse=False): # vector : [x,y]
    newVec = vectorMull(transformMat[leg], vector)
    return newVec
