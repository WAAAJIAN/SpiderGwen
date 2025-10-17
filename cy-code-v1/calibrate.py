
import maestro

servo = maestro.Controller('/dev/ttyAMA0')

calibratedleg = set()

def neutralleg(pin):
    target = 6000
    if pin[-1] == '_': 
        target = 4000
        pin = pin[:-1]
    servo.setTarget(int(pin), target)

def stopleg(pin):
    servo.setTarget(pin, 0)

try:
    while True:
        pin = input("set neutral: ")
        if pin == None or pin == '':
            print("Cleaning servos....")
            num = len(calibratedleg)
            for i in range(num):
                 leg = calibratedleg.pop()
                 stopleg(leg)
                 print(f"Servo {leg} cleaned")
        else:
            neutralleg(pin)
            if pin[-1] == '_': 
                pin = pin[:-1]
            calibratedleg.add(int(pin))
except KeyboardInterrupt:
    print("\nExiting and cleaning up...")
finally:
    for i in calibratedleg:
        stopleg(i)
    servo.close()  # This will clean up the connection
