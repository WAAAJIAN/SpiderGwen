import rclpy
from rclpy.node import Node
from std_msgs.msg import String
import sys, termios, tty, select

avail_command = {'q','w','e','a','s','d','z','x'} # gait & rotate to be added

class HexapodTeleop(Node):
    def __init__(self):
        super().__init__('hexapod_teleop')
        self.publisher = self.create_publisher(String, '/teleop_command', 10)
        self.get_logger().info("Hexapod Teleop started. Use QWEASD Keys, Ctrl+C to quit.")

    def getKey(self):
        tty.setraw(sys.stdin.fileno())
        select.select([sys.stdin], [], [], 0)
        key = sys.stdin.read(1)
        termios.tcsetattr(sys.stdin, termios.TCSADRAIN, termios.tcgetattr(sys.stdin))
        return key

    def loop(self):
        while rclpy.ok():
            key = self.getKey()
            cmd = String()
            if key == ' ':
                cmd.data = 'stop'
            elif key in avail_command:
                cmd.data = key
            else:
                continue

            self.publisher.publish(cmd)
            self.get_logger().info(f"Send command: {cmd.data}")

def main():
    rclpy.init()
    node = HexapodTeleop()
    try:
        node.loop()
    except KeyboardInterrupt:
        pass
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()