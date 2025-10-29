import rclpy
from rclpy import Node
from sensor_msgs.msg import Imu
from .gyroscope import get_gyro, MPU_Init

class IMUNode(Node):
    def __init__(self):
        super().__init__('imu_node')
        self.publisher = self.create_publisher(Imu, '/imu/data_raw', 10)
        self.timer = self.create_timer(0.05, self.loop)
        MPU_Init()
        
    def loop(self):
        Ax, Ay, Az, Gx, Gy, Gz = get_gyro()
        msg = Imu()
        msg.linear_acceleration.x = Ax
        msg.linear_acceleration.y = Ay
        msg.linear_acceleration.z = Az
        msg.angular_velocity.x = Gx
        msg.angular_velocity.y = Gy
        msg.angular_velocity.z = Gz
        self.publisher.publish(msg)

def main():
    rclpy.init()
    node = IMUNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()