from .parameter import *
from .leg import *
from queue import Queue

class Spider:
    def __init__(self):
        self.leg = {
            0: Leg(0), 
            1: Leg(1), 
            2: Leg(2), 
            3: Leg(3),
            4: Leg(4), 
            5: Leg(5) 
        }
        self.gait = gait[0]
        self.active = False
        self.move_queue = Queue() # direction string
        self.step_queue = Queue() # dict of leg target

    def add_move(self, direction_):
        self.move_queue.put(direction[direction_])

    def stop(self):
        while not self.move_queue.empty():
            try: self.move_queue.get_nowait()
            except: break

    def get_status(self):
        return self.active

    def walk(self):
        self.active = True
        leg_config = { # direction, time
            0 : [None,0],
            1 : [None,0],
            2 : [None,0],
            3 : [None,0],
            4 : [None,0],
            5 : [None,0]
        }
        curr_dir = None
        main_time = 0
        while self.active:
            move_step = dict()
            if not curr_dir: 
                if not self.move_queue.empty(): curr_dir = self.move_queue.get()
                else: curr_dir = None

            phase_offsets = [k * period for k in gait_params[self.gait]["phase_offsets"]]
            stop_time = gait_params[self.gait]["stop_time"]
            phase_count = sampling + stop_time * 2
            step = period / phase_count 
            time_on_air = gait_params[self.gait]["time_on_air"] * sampling * step
            time_on_ground = (time_on_air + stop_time * step, period - stop_time * step)

            for i in self.leg:
                if leg_config[i][0] == None:
                    if curr_dir:
                        if i in (0,4,5): leg_config[i][0] = [curr_dir[0], -curr_dir[1]]
                        else: leg_config[i][0] = curr_dir
                    
                if leg_config[i][0]:
                    direction_ = leg_config[i][0]
                    phase_time = leg_config[i][1]
        
                    if phase_time >= phase_offsets[i]:
                        if phase_time <= time_on_air:
                            phase = (phase_time * 180)/ time_on_air
                            leg_step = self.leg[i].calculateWalk(phase, direction_, walk_distance)
                        elif phase_time < time_on_ground[1] or phase_time >= time_on_ground[0]:
                            phase = 180 + ((phase_time - time_on_air) * 180)/ (time_on_ground[1] - time_on_ground[0])
                            if phase <= 360:
                                leg_step = self.leg[i].calculateWalk(phase, direction_, walk_distance)
                        
                        leg_config[i][1] += step
                        if phase_time >= period + phase_offsets[i]:
                            leg_config[i] = [None, 0]
                            if curr_dir == None: self.active = False
                        
                        if leg_step:
                            servos = spider_servo[i]
                            move_step[servos[0]] = leg_step[0]
                            move_step[servos[1]] = leg_step[1]
                            move_step[servos[2]] = leg_step[2]
            main_time += step
            if main_time >= period:
                curr_dir = None
                main_time = 0
            print(move_step)
            self.step_queue.put(move_step)

    def step(self):
        if not self.step_queue.empty:
            return self.step_queue.get()
        return None

    def gaitChange(self, inp):
        self.gait = gait[inp]
