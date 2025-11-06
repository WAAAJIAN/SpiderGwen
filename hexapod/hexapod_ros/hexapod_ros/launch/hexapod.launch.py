from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os 

def generate_launch_description():
    config_file = os.path.join(
        get_package_share_directory('hexapod_ros'), 'config', 'pid_params.yaml'
    )
    return LaunchDescription([
        Node(package='hexapod_ros', executable='imu_node'),
        Node(package='hexapod_ros', executable='hexapod_controller', parameters=[config_file]),
        Node(package='hexapod_ros', executable='maestro_driver'),
    ])