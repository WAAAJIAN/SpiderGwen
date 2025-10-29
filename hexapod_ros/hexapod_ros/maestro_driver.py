import rclpy
from rclpy.node import Node
from std_msgs.msg import Float32MultiArray
from hexapod_ros.msg import ServoTarget
from hexapod_ros.msg import ServoTargetArray
from .maestro import Controller

class MaestroDriver(Node):
    def __init__(self):
        super().__init__('maestro_driver')
        self.controller= Controller('/dev/ttyAMA0')
        self.create_subscription(ServoTargetArray, '/hexapod/servo_targets', self.callback, 10)

    def callback(self, msg):
        for data in (msg.targets):
            servo_id = data.servo_id
            target_position = data.target_position
            self.controller.setTarget(servo_id, target_position)
        
def main():
    rclpy.init()
    node = MaestroDriver()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()