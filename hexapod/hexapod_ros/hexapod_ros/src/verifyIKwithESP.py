from leg import Leg

# Create leg 0 for example
leg = Leg(0)

# Test position (same as ESP32 test)
x = 0
y = 150
z = 150

leg.x = x
leg.y = y
leg.z = z

leg.IK()

print("Python IK:")
print("Coxa:", leg.a)
print("Femur:", leg.b)
print("Tibia:", leg.c)
