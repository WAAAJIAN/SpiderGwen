import rclpy
from rclpy.node import Node
from rclpy.action import ActionClient
from hexapod_msgs.action import Servo
from hexapod_msgs.msg import ServoTarget
from hexapod_msgs.msg import ServoTargetArray
from sensor_msgs.msg import Imu
from std_msgs.msg import String
from .spider import Spider
from time import sleep

class HexapodController(Node):
    def __init__(self):
        super().__init__('hexapod_controller')
        self.spider = Spider()
        self.create_subscription(String, '/teleop_command', self.teleop_cb, 10)
        # self.create_subscription(Imu, '/imu/data_raw', self.imu_cb, 10)
        # self.servo_pub = self.create_publisher(ServoTargetArray, '/hexapod/servo_targets', 10)
        self._action_client = ActionClient(self, Servo, 'servo_action')
        self.timer = self.create_timer(0.05, self.loop)
        self.active = False
    
    def teleop_cb(self, msg):
        command = msg.data
        if command == 'stop':
            self.spider.stop()
        else:
            self.get_logger().info(f"Receive command: {command}")
            self.spider.add_move(command) 
            self.active = True

    def imu_cb(self, msg):
        Ax = msg.linear_acceleration.x
        Ay = msg.linear_acceleration.y
        Az = msg.linear_acceleration.z
        Gx = msg.angular_acceleration.x
        Gy = msg.angular_acceleration.y
        Gz = msg.angular_acceleration.z
        pass
        # self.spider.update_imu(Ax, Ay, Az, Gx, Gy, Gz)

    def send_goal(self, goal):
        goal_msg = Servo.Goal()
        goal_msg.servo_targets = goal
        self._action_client.wait_for_server()
        self._send_goal_future = self._action_client.send_goal_async(goal_msg)
        self._send_goal_future.add_done_callback(self.goal_response_callback)

    def goal_response_callback(self, future):
        goal_handle = future.result()
        if not goal_handle.accepted:
            self.get_logger().info('Goal rejected :(')
            return
        self.get_logger().info('Goal accepted :)')
        self._get_result_future = goal_handle.get_result_async()
        self._get_result_future.add_done_callback(self.get_result_callback)

    def get_result_callback(self, future):
        result = future.result().result
        self.get_logger().info(f'Result: success={result.success}"')

    def loop(self):
        if self.active:
            self.spider.walk()
            action = self.spider.step()
            self.get_logger().info(f"Received target: {action}")
            result = ServoTargetArray()
            for leg, servos in action.items():
                for servo in servos:
                    submsg = ServoTarget()
                    submsg.servo_id = servo[0]
                    submsg.target_position = servo[1]
                    result.targets.append(submsg)
            if result.targets: self.send_goal(result)
            else: self.acitve = False

def main():
    rclpy.init()
    node = HexapodController()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

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
