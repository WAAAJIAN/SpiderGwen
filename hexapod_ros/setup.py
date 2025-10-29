from setuptools import find_packages, setup

package_name = 'hexapod_ros'

setup(
    name=package_name,
    version='0.0.0',
    packages=['hexapod_ros'],
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools', 'colcon-common-extensions'],
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
            'teleop_node = hexapod_ros.teleop_node:main',
        ],
    },
    package_data={
        '': ['resource/*'],
    },
)
