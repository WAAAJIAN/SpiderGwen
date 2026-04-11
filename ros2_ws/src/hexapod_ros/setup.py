from setuptools import find_packages, setup
package_name = 'hexapod_ros'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        ('share/' + package_name + '/launch', ['launch/hexapod.launch.py']),
        ('share/' + package_name + '/config', ['config/pid_params.yaml'])
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='vboxuser',
    maintainer_email='vboxuser@todo.todo',
    description='TODO: Package description',
    license='TODO: License declaration',
    extras_require={
        'test': [
            'pytest',
        ],
    },
    entry_points={
        'console_scripts': [
            'imu_node = src.imu_node:main',
            'teleop = src.hexapod_teleop:main',
            'hexapod_controller = src.hexapod_controller:main',
            'maestro_driver = src.maestro_driver:main',
        ],
    },
    package_data={
        '': ['resource/*'],
    },
)
