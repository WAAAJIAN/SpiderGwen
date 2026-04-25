## esp32_interface.py
## UART bridge between RPi and ESP32.
##
## Protocol:
##   L,leg_id,x,y,z\n  — set foot position target for one leg
##   STAND\n            — trigger stand sequence on ESP32

import serial


class ESP32Interface:
    def __init__(self, port="/dev/ttyUSB0", baud=115200):
        self.ser = serial.Serial(port, baud, timeout=0.01)

    def send_leg_xyz(self, leg_id, x, y, z):
        """Send a foot position target for one leg."""
        msg = f"L,{leg_id},{x:.3f},{y:.3f},{z:.3f}\n"
        self.ser.write(msg.encode())

    def send_command(self, cmd):
        """Send a general command string (e.g. 'STAND')."""
        msg = f"{cmd}\n"
        self.ser.write(msg.encode())