import serial

class ESP32Interface:

    def __init__(self, port="/dev/ttyUSB0", baud=115200):
        self.ser = serial.Serial(port, baud, timeout=0.01)

    def send(self, action):
        """
        action = output of spider.step()
        """

        msg = ""

        for leg in action:
            for servo_id, angle in action[leg]:
                msg += f"{servo_id}:{angle},"

        msg += "\n"

        self.ser.write(msg.encode())
