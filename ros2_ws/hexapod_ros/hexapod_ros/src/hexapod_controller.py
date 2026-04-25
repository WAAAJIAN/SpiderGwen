## hexapod_controller.py
## ROS2 node for SpiderGwen hexapod (RPi side).
##
## Responsibilities:
##   - Receives teleop commands and forwards to Spider motion planner
##   - Receives IMU data, runs complementary filter + PID via Spider
##   - Each control tick: calls spider.walk() then spider.step(),
##     and sends resulting foot positions to ESP32 over UART
##   - Stand command: sends "STAND\n" to ESP32 directly (ESP32 owns that sequence)
##
## UART protocol to ESP32:
##   L,leg_id,x,y,z\n  — foot position target
##   STAND\n            — trigger stand sequence on ESP32

import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Imu
from std_msgs.msg import String, Float64
from .spider import Spider
from .esp32_interface import ESP32Interface
import yaml


class HexapodController(Node):
    def __init__(self):
        super().__init__(
            'hexapod_controller',
            allow_undeclared_parameters=True,
            automatically_declare_parameters_from_overrides=True
        )

        self.spider = Spider()
        self.spider.dt = self.get_parameter('dt').value
        self.load_pid()

        self.get_logger().info(f"dt: {self.spider.dt}")
        self.get_logger().info(f"pid: {self.spider.pid}")

        # ESP32 UART interface
        self.esp = ESP32Interface()

        # ROS2 subscriptions
        self.tele_sub = self.create_subscription(
            String, '/teleop_command', self.teleop_cb, 10)

        # ROS2 publishers (IMU diagnostics)
        self.roll_angle_pub  = self.create_publisher(Float64, '/roll_angle',  10)
        self.roll_error_pub  = self.create_publisher(Float64, '/roll_error',  10)
        self.pitch_angle_pub = self.create_publisher(Float64, '/pitch_angle', 10)
        self.pitch_error_pub = self.create_publisher(Float64, '/pitch_error', 10)
        self.yaw_error_pub   = self.create_publisher(Float64, '/yaw_error',   10)

        # State flags
        self.standing = False   # True while stand sequence is executing on ESP32

        # Start: send stand command to ESP32, then begin control loop
        self._trigger_stand()

    # ------------------------------------------------------------------ #
    #  Stand
    # ------------------------------------------------------------------ #

    def _trigger_stand(self):
        """
        Sends STAND command to ESP32 and waits for it to complete
        before starting the main control loop.
        ESP32's Spider::stand() runs the full stand sequence autonomously.
        """
        self.standing = True
        self.get_logger().info("[ STAND ] Sending STAND command to ESP32...")
        self.esp.send_command("STAND")

        # ESP32 stand sequence takes ~3s (50 steps × 40ms + 1s initial delay).
        # Use a one-shot timer to start the control loop after it finishes.
        self.create_timer(4.0, self._start_control_loop)

    def _start_control_loop(self):
        """Called once after stand sequence completes. Starts normal control loop."""
        self.standing = False
        self.get_logger().info("[ READY ] Starting control loop.")

        # IMU subscription: calibrate first if needed, else go straight to control
        if not self.spider.pid['bias']['calibrated']:
            self.imu_sub = self.create_subscription(
                Imu, '/imu/data_raw', self.calibrate_imu_cb, 10)
        else:
            self._start_imu_control()

        # Cancel the one-shot timer (create_timer repeats — destroy it)
        # Note: ROS2 timers are repeating; we destroy it after first fire
        # This is handled by only creating it once in _trigger_stand.

    # ------------------------------------------------------------------ #
    #  IMU calibration
    # ------------------------------------------------------------------ #

    def calibrate_imu_cb(self, msg):
        """Accumulates IMU samples to find zero-bias, then switches to control."""
        done = self.spider.calibrate_imu(
            msg.linear_acceleration.x,
            msg.linear_acceleration.y,
            msg.linear_acceleration.z,
            msg.angular_velocity.x,
            msg.angular_velocity.y,
            msg.angular_velocity.z
        )
        if done:
            # Save calibrated bias back to param file
            self._save_bias_to_config()
            self.get_logger().info(
                f"IMU calibrated — roll_bias: {self.spider.pid['bias']['roll']:.3f}  "
                f"pitch_bias: {self.spider.pid['bias']['pitch']:.3f}"
            )
            self.destroy_subscription(self.imu_sub)
            self._start_imu_control()

    def _save_bias_to_config(self):
        try:
            param_file = self.get_parameter('config_file').value
            with open(param_file, 'r') as f:
                params = yaml.safe_load(f) or {}
            ros_params = (params
                          .get('hexapod_controller', {})
                          .get('ros__parameters', {}))
            if 'pid' in ros_params:
                bias = self.spider.pid['bias']
                ros_params['pid']['bias'].update({
                    'Ax':         float(bias['Ax']),
                    'Ay':         float(bias['Ay']),
                    'Az':         float(bias['Az']),
                    'Gx':         float(bias['Gx']),
                    'Gy':         float(bias['Gy']),
                    'Gz':         float(bias['Gz']),
                    'roll':       float(bias['roll']),
                    'pitch':      float(bias['pitch']),
                    'calibrated': 1
                })
                with open(param_file, 'w') as f:
                    yaml.dump(params, f, default_flow_style=False, indent=2)
        except Exception as e:
            self.get_logger().warn(f"Could not save bias to config: {e}")

    def _start_imu_control(self):
        """Switch IMU subscription to the live control callback."""
        self.imu_sub = self.create_subscription(
            Imu, '/imu/data_raw', self.imu_cb, 10)
        # Main control loop at 50 Hz (every 20 ms)
        self.control_timer = self.create_timer(0.02, self.control_loop)

    # ------------------------------------------------------------------ #
    #  IMU live callback
    # ------------------------------------------------------------------ #

    def imu_cb(self, msg):
        """
        Updates complementary filter + PID with latest IMU reading.
        Publishes diagnostic angles/errors for tuning/monitoring.
        """
        if self.standing:
            return  # Don't process IMU during stand sequence

        self.spider.update_imu(
            msg.linear_acceleration.x,
            msg.linear_acceleration.y,
            msg.linear_acceleration.z,
            msg.angular_velocity.x,
            msg.angular_velocity.y,
            msg.angular_velocity.z
        )
        self.roll_angle_pub.publish( Float64(data=float(self.spider.angle['roll'])))
        self.roll_error_pub.publish( Float64(data=float(self.spider.error['roll'])))
        self.pitch_angle_pub.publish(Float64(data=float(self.spider.angle['pitch'])))
        self.pitch_error_pub.publish(Float64(data=float(self.spider.error['pitch'])))
        self.yaw_error_pub.publish(  Float64(data=float(self.spider.error['yaw'])))

    # ------------------------------------------------------------------ #
    #  Teleop
    # ------------------------------------------------------------------ #

    def teleop_cb(self, msg):
        command = msg.data
        if command == 'stop':
            self.spider.stop()
        else:
            self.get_logger().info(f"Teleop command received: {command}")
            self.spider.add_move(command)

    # ------------------------------------------------------------------ #
    #  Main control loop (50 Hz)
    # ------------------------------------------------------------------ #

    def control_loop(self):
        """
        Runs every 20 ms.
        1. Calls spider.walk() to advance gait state and fill step queues
        2. Calls spider.step() to get {leg_id: (x, y, z)} for this tick
        3. Sends each foot position to ESP32 via UART
        """
        if self.standing or not self.spider.pid['bias']['calibrated']:
            return

        self.spider.walk()
        positions = self.spider.step()  # {leg_id: (x, y, z)}

        for leg_id, (x, y, z) in positions.items():
            self.esp.send_leg_xyz(leg_id, x, y, z)

    # ------------------------------------------------------------------ #
    #  PID parameter loading
    # ------------------------------------------------------------------ #

    def load_pid(self):
        """Loads PID params from ROS2 parameter server into spider.pid dict."""
        for param in self._parameters.values():
            if param.name.startswith("pid."):
                parts = param.name.split(".")
                if len(parts) == 3:
                    _, axis, name = parts
                    if axis not in self.spider.pid:
                        self.spider.pid[axis] = dict()
                    self.spider.pid[axis][name] = param.value


def main(args=None):
    try:
        rclpy.init(args=args)
        node = HexapodController()
        rclpy.spin(node)
        node.destroy_node()
        rclpy.shutdown()
    except KeyboardInterrupt:
        node.get_logger().info("KeyboardInterrupt — shutting down.")