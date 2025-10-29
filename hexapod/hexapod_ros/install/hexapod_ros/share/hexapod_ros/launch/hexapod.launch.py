from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        # Node(package='hexapod_ros', executable='imu_node'),
        Node(package='hexapod_ros', executable='hexapod_controller'),
        Node(package='hexapod_ros', executable='maestro_driver'),
    ])