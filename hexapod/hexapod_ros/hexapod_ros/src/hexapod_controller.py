import rclpy
from rclpy.node import Node
from rclpy.action import ActionClient
from hexapod_msgs.action import Servo
from hexapod_msgs.msg import ServoTarget
from hexapod_msgs.msg import ServoTargetArray
from sensor_msgs.msg import Imu
from std_msgs.msg import String
from std_msgs.msg import Float64
from .spider import Spider
from time import sleep
import yaml
from rclpy.parameter import Parameter


class HexapodController(Node):
    def __init__(self):
        super().__init__('hexapod_controller', allow_undeclared_parameters=True, automatically_declare_parameters_from_overrides=True)
        self.spider = Spider()
        self.spider.dt = self.get_parameter('dt').value
        self.load_pid()
        self.get_logger().info(f"{self.spider.dt}")
        self.get_logger().info(f"{self.spider.pid}")
        self.create_subscription(String, '/teleop_command', self.teleop_cb, 10)
        self.create_subscription(Imu, '/imu/data_raw', self.imu_cb, 10)
        self.roll_pub = self.create_publisher(Float64, '/roll', 10)
        # self.pitch_pub = self.create_publisher(Float64, '/pitch', 10)
        self._action_client = ActionClient(self, Servo, 'servo_action')
        self.timer = self.create_timer(0.12, self.stand)
        self.active = False
        self.stand = False
        # initialize stand motion
        self.actionlst = self.spider.stand()

    
    def teleop_cb(self, msg):
        command = msg.data
        if command == 'stop':
            self.spider.stop()
        else:
            self.get_logger().info(f"Receive command: {command}")
            self.spider.add_move(command) 

    def imu_cb(self, msg):
        Ax = msg.linear_acceleration.x
        Ay = msg.linear_acceleration.y
        Az = msg.linear_acceleration.z
        Gx = msg.angular_velocity.x
        Gy = msg.angular_velocity.y
        Gz = msg.angular_velocity.z
        if not self.stand:
            self.get_logger().info(f"{Ax,Ay,Az,Gx,Gy,Gz}")
            self.spider.update_imu(Ax, Ay, Az, Gx, Gy, Gz)
            res = self.spider.rbias()
            self.get_logger().info(f"{res[0], res[1], res[2], res[3], res[4]}")
            self.get_logger().info(f"roll: {self.spider.error['roll']} pitch: {self.spider.error['pitch']}")
            self.get_logger().info(f"roll_sum: {self.spider.error_sum['roll']} pitch_sum: {self.spider.error_sum['pitch']}\n")
            self.roll_pub.publish(Float64(data=float(self.spider.error['roll'])))
            # self.pitch_pub.publish(Float64(data=float(self.spider.error['pitch'])))


    def send_goal(self, goal):
        goal_msg = Servo.Goal()
        goal_msg.servo_targets = goal
        self._action_client.wait_for_server()
        self._send_goal_future = self._action_client.send_goal_async(goal_msg)
        self._send_goal_future.add_done_callback(self.goal_response_callback)

    def goal_response_callback(self, future):
        goal_handle = future.result()
        if not goal_handle.accepted: return
        self._get_result_future = goal_handle.get_result_async()
        self._get_result_future.add_done_callback(self.get_result_callback)

    def get_result_callback(self, future):
        result = future.result().result
        self.active = False

    def stand(self):
        if self.spider.bias_added:
            self.stand = True
            if self.actionlst:
                if not self.active:
                    self.active = True
                    action = self.actionlst.pop(0)
                    result = ServoTargetArray()
                    for servo in action:
                        submsg = ServoTarget()
                        submsg.servo_id = servo[0]
                        submsg.target_position = servo[1]
                        result.targets.append(submsg)
                    self.send_goal(result)
            else:
                self.stand = False
                self.timer.cancel()
                self.timer = self.create_timer(0.12, self.loop)

    def loop(self):
        if not self.active:
            self.active = True
            try:
                self.spider.walk()
                action = self.spider.step()
                # self.get_logger().info(f"Received target: {action}")
                # for leg, config in self.spider.leg.items():
                #     self.get_logger().info(f"leg: {leg}, dir: {config[1]}, time, {config[2]}")
                # self.get_logger().info(f"time: {self.spider.main_time}, direction: {self.spider.curr_move}\n")            
                if action:
                    result = ServoTargetArray()
                    for leg, servos in action.items():
                        for servo in servos:
                            submsg = ServoTarget()
                            submsg.servo_id = servo[0]
                            submsg.target_position = servo[1]
                            result.targets.append(submsg)
                    self.send_goal(result)
            except:
                self.active = False
                return

    def load_pid(self):
        for param in self._parameters.values():
            if param.name.startswith("pid."):
                parts = param.name.split(".")
                if len(parts) != 3: continue  
                _, axis, name = parts
                if axis not in self.spider.pid:
                    self.spider.pid[axis] = dict()
                self.spider.pid[axis][name] = param.value

def main(args=None):
    try:
        rclpy.init(args=args)
        node = HexapodController()
        rclpy.spin(node)
        node.destroy_node()
        rclpy.shutdown()
    except KeyboardInterrupt:
        node.get_logger().info("KeyboardInterrupt received...")


# def load_pid_params(node, prefix="pid"):
#     pid_dict = dict()
#     for param in node.list_parameters([prefix], depth=5).names:
#         parts = param.split(".")
#         if len(parts) != 3: continue  
#         _, axis, name = parts
#         if axis not in pid_dict:
#             pid_dict[axis] = dict()
#         pid_dict[axis][name] = node.get_parameter(param).double_value
#     return pid_dict