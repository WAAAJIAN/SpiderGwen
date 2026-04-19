import serial

class ESP32Interface:

    def __init__(self, port="/dev/ttyUSB0", baud=115200):
        self.ser = serial.Serial(port, baud, timeout=0.01)

    # send desired leg position command to ESP32, format: L,leg_id,x,y,z
    def send_leg_xyz(self, leg_id, x, y, z):
        msg = f"L,{leg_id},{x},{y},{z}\n"
        self.ser.write(msg.encode())
