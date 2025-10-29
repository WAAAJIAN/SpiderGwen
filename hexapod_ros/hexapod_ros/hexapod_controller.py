import rclpy
from rclpy.node import Node
from hexapod_ros.msg import ServoTarget
from hexapod_ros.msg import ServoTargetArray
from sensor_msgs.msg import Imu
from std_msgs.msg import String
from .spider import Spider
import threading

class HexapodController(Node):
    def __init__(self):
        super().__init__('hexapod_controller')
        self.spider = Spider()
        # run a stand up script here
        self.create_subscription(String, '/teleop_command', self.teleop_cb, 10)
        self.create_subscription(Imu, '/imu/data_raw', self.imu_cb, 10)
        self.servo_pub = self.create_publisher(ServoTargetArray, '/hexapod/servo_targets', 10)
        self.timer = self.create_timer(0.05, self.loop)
        self.active = False
    
    def teleop_cb(self, msg):
        command = msg.data
        if command == 'stop':
            self.spider.stop()
        else:
            self.spider.add_move(command)
            if not self.spider.get_status:
                self.active = True
                threading.Thread(target=self.spider.walk())

    def imu_cb(self, msg):
        Ax = msg.linear_acceleration.x
        Ay = msg.linear_acceleration.y
        Az = msg.linear_acceleration.z
        Gx = msg.angular_acceleration.x
        Gy = msg.angular_acceleration.y
        Gz = msg.angular_acceleration.z
        pass
        # self.spider.update_imu(Ax, Ay, Az, Gx, Gy, Gz)
    
    def loop(self):
        if self.active:
            servo_targets = self.spider.step() # dict()
            if servo_targets:
                msg = ServoTargetArray()
                msg.data = []
                for servo, targets in servo_targets.items():
                    submsg = ServoTarget()
                    submsg.servo_id = servo
                    submsg.target_position = targets
                    msg.targets.append(submsg)
                self.publisher.publish(msg)
            else:
                self.active = False

def main():
    rclpy.init()
    node = HexapodController()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()