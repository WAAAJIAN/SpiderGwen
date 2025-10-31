import rclpy
from rclpy.node import Node
from std_msgs.msg import Float32MultiArray
from hexapod_msgs.msg import ServoTarget
from hexapod_msgs.msg import ServoTargetArray
from rclpy.action import ActionServer
from hexapod_msgs.action import Servo
from .maestro import Controller

class MaestroDriver(Node):
    def __init__(self):
        super().__init__('maestro_driver')
        self.controller= Controller('/dev/ttyAMA0')
        self._action_server = ActionServer(self, Servo, 'servo_action', self.execute_callback)

    async def execute_callback(self, goal):
        # self.get_logger().info(f"Received target: {goal.request.servo_targets}")

        for data in goal.request.servo_targets.targets:
            servo_id = data.servo_id
            target_position = data.target_position
            self.controller.setTarget(servo_id, target_position)
        goal.succeed()

        result = Servo.Result()
        result.success = True
        return result
        
def main():
    rclpy.init()
    node = MaestroDriver()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()