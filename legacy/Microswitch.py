import RPi.GPIO as GPIO   #error will disappear when running on rpi
import time

# GPIO numbers for each leg's microswitch
SWITCH_PINS = {
    1: 17,
    2: 22,
    3: 23,
    4: 24,
    5: 25,
    6: 27
}

# Setup
GPIO.setmode(GPIO.BCM)
for pin in SWITCH_PINS.values():
    GPIO.setup(pin, GPIO.IN, pull_up_down=GPIO.PUD_UP)

try:
    while True:
        for leg, pin in SWITCH_PINS.items():
            if GPIO.input(pin) == GPIO.LOW:
                print(f"Leg {leg} touched ground!")
            else:
                print(f"Leg {leg} in the air.")
        time.sleep(0.1)

except KeyboardInterrupt:
    GPIO.cleanup()
