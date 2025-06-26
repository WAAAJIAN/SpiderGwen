import time
import maestro

# Create the servo controller instance
servo = maestro.Controller()  # use default tty; modify with e.g. '/dev/ttyACM0' if needed

# Define all legs and their servo channel mappings
legs = {
    "L1": [0, 1, 2],
    "L2": [3, 4, 5],
    "L3": [6, 7, 8],
    "R3": [9, 10, 11],
    "R2": [18, 19, 20],
    "R1": [21, 22, 23]
}

# Set a safe range of angles in microseconds (6000 = 90°, ~5000 = 0°, ~7000 = 180°)
positions = [5000, 6000, 7000]

def move_leg(name, channels):
    print(f"Testing leg {name}...")
    for pos in positions:
        print(f" → Setting to {pos}")
        for ch in channels:
            servo.setTarget(ch, pos)
        time.sleep(1)

def center_all():
    print("Centering all legs...")
    for chs in legs.values():
        for ch in chs:
            servo.setTarget(ch, 6000)
    time.sleep(2)

def main():
    center_all()
    for leg_name, channels in legs.items():
        move_leg(leg_name, channels)
    print("✅ All legs tested.")

main()
