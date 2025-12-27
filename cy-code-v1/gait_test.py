from parameter import *
import matplotlib.pyplot as plt
import numpy as np

gait = gait[0]
direction = [1,0] # w

movement = {i:[] for i in range(6)}

def walkCycle(direction):
    time_on_air = gait_params[gait]["time_on_air"] * period
    phase_offsets = gait_params[gait]["phase_offsets"]
    walk(direction, 1, time_on_air, phase_offsets)

def walk( direction, type_, time_on_air, phase_offsets):        
    distance = 50
    time = 0
    while(time <= 2 * period - time_on_air):            
        for i in range(1,2):
            if time >= phase_offsets[i] * period:
                leg_time = time - phase_offsets[i] * period
                if leg_time <= time_on_air:
                    phase = (leg_time * 180)/time_on_air
                    calculateWalk(i, phase, direction, distance, type_)
                # else:
                #     phase = 180 + ((leg_time - time_on_air) * 180)/(period - time_on_air)
                #     if phase <= 360:
                #         calculateWalk(i, phase, direction, distance, type_)
        time += steps
    time = 0

def calculateWalk(leg, phase, direction, distance, type_):
    if phase <= 180:
        turn_distance = walk_cycle["on_air"][type_] * distance
        x = direction[0] * turn_distance * cos(radians(180 - phase)) + distance * walk_offset[type_]
        y = -direction[1] * turn_distance * (cos(radians(phase)) * -0.5 + 0.5)
        # z = - distance * sin(radians(phase)) + z_offset
    else:
        turn_distance = walk_cycle["on_ground"][type_] * distance
        x = direction[0] * turn_distance * ((phase/180) - 1) 
        y = -direction[1] * turn_distance * (cos(radians(phase)) * -0.5 + 0.5)
        # z = z_offset
    new_vec = transformBodyCoortoLeg(leg, [x,y]) # relative to initial offset
    # new_vec = [x,y]
    if leg in (0,5,4):
        new_vec = [new_vec[0], -new_vec[1]]
    if leg in (2,5):
        x = new_vec[0]  
        y = y_offset + new_vec[1] + ctc[0] if leg == 2 else (ctc[0] + y_offset) * -1 + new_vec[1]
    else:
        x = (ctc[1] + y_offset + new_vec[0]) #* sin(radians(offset_angle_map[leg]))
        y = (ctc[1] + y_offset + new_vec[1]) #* cos(radians(offset_angle_map[leg]))
    movement[leg].append(new_vec    )

walkCycle(direction)

# plot results
fig, ax = plt.subplots(figsize=(8,8))
colors = plt.cm.get_cmap('tab10', 6)  # 6 distinct colors

for leg in range(6):
    pts = np.array(movement[leg])
    if pts.size == 0:
        continue
    xs, ys = pts[:,0], pts[:,1]
    ax.plot(xs, ys, '-', color=colors(leg), label=f'leg {leg}')
    ax.scatter(xs, ys, s=12, color=colors(leg))

ax.set_aspect('equal', 'box')
ax.set_xlabel('X (mm)')
ax.set_ylabel('Y (mm)')
ax.set_title('Leg movement trajectories')
ax.grid(True)
ax.legend(loc='best')
plt.show()