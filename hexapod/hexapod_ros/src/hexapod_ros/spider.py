from .parameter import *
from .leg import *
from queue import Queue
import rclpy
from rclpy.node import Node
from rclpy.action import ActionServer
from hexapod_msgs.action import Walk
from hexapod_msgs.msg import ServoTarget
from hexapod_msgs.msg import ServoTargetArray

class Spider(Node):
    def __init__(self):
        super().__init__('spider')
        self.leg = { # leg, direction, time
            0: [Leg(0), None, 0], 
            1: [Leg(1), None, 0], 
            2: [Leg(2), None, 0], 
            3: [Leg(3), None, 0],
            4: [Leg(4), None, 0], 
            5: [Leg(5), None, 0] 
        }
        self.gait = gait[0]
        self.active = False
        self.move_queue = Queue() # direction 
        self.step_queue = {
            0 : Queue(),
            1 : Queue(),
            2 : Queue(),
            3 : Queue(),
            4 : Queue(),
            5 : Queue()
        }
        self.curr_move = None
        self.main_time = 0
        self._action_server = ActionServer(self, Walk, 'walk_action', self.execute_callback)

    def add_move(self, direction_):
        self.move_queue.put(direction[direction_])

    def stop(self):
        while not self.move_queue.empty():
            try: self.move_queue.get_nowait()
            except: break

    def get_status(self):
        return self.active

    async def execute_callback(self, goal_handle):
        self.get_logger().info(f"Received goal...")
        state = self.walk()
        if state:
            goal_handle.succeed()
            result = ServoTargetArray()
            for leg in range(6):
                if not self.step_queue[leg].empty():
                    servo_lst = self.step_queue[leg].get()
                    for servo in servo_lst:
                        submsg = ServoTarget()
                        submsg.servo_id = servo[0]
                        submsg.target_position = servo[1]
                        result.targets.append(submsg)
            if result.targets: return result  
            else: return None
        else: goal_handle.abort()

    def walk(self): # one cycle took 5ms at most to calculate
        try:
            if not self.curr_move: 
                if not self.move_queue.empty(): self.curr_move = self.move_queue.get()
                else: self.curr_move = None

            phase_offsets = [k * period for k in gait_params[self.gait]["phase_offsets"]]
            stop_time = gait_params[self.gait]["stop_time"]
            phase_count = sampling + stop_time * 2
            step = period / phase_count 
            time_on_air = gait_params[self.gait]["time_on_air"] * sampling * step
            time_on_ground = (time_on_air + stop_time * step, period - stop_time * step)

            for i in self.leg:
                if self.leg[i][1] == None:
                    if self.curr_move:
                        if i in (0,4,5): self.leg[i][1] = [self.curr_move[0], -self.curr_move[1]]
                        else: self.leg[i][1] = self.curr_move
                    
                if self.leg[i][1]:
                    direction_ = self.leg[i][1]
                    phase_time = self.leg[i][2]
        
                    if phase_time >= phase_offsets[i]:
                        if phase_time <= time_on_air:
                            phase = (phase_time * 180)/ time_on_air
                            leg_step = self.leg[i].calculateWalk(phase, direction_, walk_distance)
                        elif phase_time < time_on_ground[1] or phase_time >= time_on_ground[0]:
                            phase = 180 + ((phase_time - time_on_air) * 180)/ (time_on_ground[1] - time_on_ground[0])
                            if phase <= 360:
                                leg_step = self.leg[i].calculateWalk(phase, direction_, walk_distance)
                        
                        self.leg[i][2] += step
                        if phase_time >= period + phase_offsets[i]:
                            self.leg[i] = [None, 0]
                            # if self.curr_move == None: self.active = False
                        
                        if leg_step:
                            servos = spider_servo[i]
                            for k in range(3):
                                self.step_queue[i].put([servos[k], leg_step[k]])
            self.main_time += step
            if self.main_time >= period:
                self.curr_move = None
                self.main_time = 0
            return True
        except:
            return False

    def step(self):
        if not self.step_queue.empty:
            return self.step_queue.get()
        return None

    def gaitChange(self, inp):
        self.gait = gait[inp]
