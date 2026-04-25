## imu_node.py
## ROS2 node that reads MPU6050 data and publishes to /imu/data_raw at 500Hz.
## Consumed by hexapod_controller.py for complementary filter + PID balance.

import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Imu
from .gyroscope import MPU6050


class IMUNode(Node):
    def __init__(self):
        super().__init__('imu_node')
        self.imu = MPU6050()  # initialises device on construction
        self.publisher = self.create_publisher(Imu, '/imu/data_raw', 10)
        self.timer = self.create_timer(0.002, self.loop)
        self.get_logger().info("IMU node started, publishing to /imu/data_raw at 500Hz.")

    def loop(self):
        Ax, Ay, Az, Gx, Gy, Gz = self.imu.get_gyro()
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
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        node.get_logger().info("IMU node shutting down.")
    node.destroy_node()
    rclpy.shutdown()