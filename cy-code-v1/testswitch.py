import RPi.GPIO as GPIO
import time

btn = 4
GPIO.setmode(GPIO.BCM)

GPIO.setup(btn, GPIO.IN, pull_up_down=GPIO.PUD_OFF)

try:
    while True:
        if GPIO.input(btn) == GPIO.LOW:
            print("pressed")
        else:
            print("released")
        time.sleep(0.1)

except KeyboardInterrupt:
    print("exiting...")
finally:
    GPIO.cleanup()