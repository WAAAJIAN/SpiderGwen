## gyroscope.py
## MPU6050 I2C driver for SpiderGwen RPi side.
## Reads raw accelerometer and gyroscope data and converts to physical units:
##   Accelerometer → m/s²
##   Gyroscope     → °/s

import smbus2
from time import sleep

# MPU6050 register addresses
PWR_MGMT_1   = 0x6B
SMPLRT_DIV   = 0x19
CONFIG       = 0x1A
GYRO_CONFIG  = 0x1B
INT_ENABLE   = 0x38
ACCEL_XOUT_H = 0x3B
ACCEL_YOUT_H = 0x3D
ACCEL_ZOUT_H = 0x3F
GYRO_XOUT_H  = 0x43
GYRO_YOUT_H  = 0x45
GYRO_ZOUT_H  = 0x47

# Scale factors
ACCEL_SCALE  = 16384.0  # LSB/(m/s²) for ±2g full scale
GYRO_SCALE   = 131.0    # LSB/(°/s)  for ±250°/s full scale (GYRO_CONFIG = 0x00)
# NOTE: if GYRO_CONFIG is set to 0x18 (±2000°/s), use 16.4 instead

DEVICE_ADDRESS = 0x68


class MPU6050:
    def __init__(self, bus_number=1):
        self.bus = smbus2.SMBus(bus_number)
        self._init_device()

    def _init_device(self):
        self.bus.write_byte_data(DEVICE_ADDRESS, SMPLRT_DIV, 7)   # sample rate = 8kHz / (7+1) = 1kHz
        self.bus.write_byte_data(DEVICE_ADDRESS, PWR_MGMT_1,  1)   # wake device, use X gyro as clock
        self.bus.write_byte_data(DEVICE_ADDRESS, CONFIG,      0)   # no DLPF
        self.bus.write_byte_data(DEVICE_ADDRESS, GYRO_CONFIG, 0)   # ±250°/s — matches GYRO_SCALE above
        self.bus.write_byte_data(DEVICE_ADDRESS, INT_ENABLE,  1)   # data ready interrupt

    def _read_raw(self, addr):
        high  = self.bus.read_byte_data(DEVICE_ADDRESS, addr)
        low   = self.bus.read_byte_data(DEVICE_ADDRESS, addr + 1)
        value = (high << 8) | low
        if value > 32768:
            value -= 65536
        return value

    def get_gyro(self):
        """
        Returns [Ax, Ay, Az, Gx, Gy, Gz]:
          Ax, Ay, Az — linear acceleration in m/s²
          Gx, Gy, Gz — angular velocity in °/s
        Note: Az is negated because the IMU is mounted upside-down on this robot.
        """
        Ax =  self._read_raw(ACCEL_XOUT_H) * 9.81 / ACCEL_SCALE
        Ay =  self._read_raw(ACCEL_YOUT_H) * 9.81 / ACCEL_SCALE
        Az = -self._read_raw(ACCEL_ZOUT_H) * 9.81 / ACCEL_SCALE  # inverted mount

        Gx = self._read_raw(GYRO_XOUT_H) / GYRO_SCALE
        Gy = self._read_raw(GYRO_YOUT_H) / GYRO_SCALE
        Gz = self._read_raw(GYRO_ZOUT_H) / GYRO_SCALE

        return [Ax, Ay, Az, Gx, Gy, Gz]