from .leg import Leg

# Create leg 0 for example
leg = Leg(0)

leg.x = 0
leg.y = 150
leg.z = 150

leg.IK()

print("Python IK for (0, 150, 150):")
print("Coxa:", leg.a)
print("Femur:", leg.b)
print("Tibia:", leg.c)

leg.x = 30
leg.y = 150
leg.z = 120

leg.IK()

print("Python IK for (30, 150, 120):")
print("Coxa:", leg.a)
print("Femur:", leg.b)
print("Tibia:", leg.c)

leg.x = -30
leg.y = 150
leg.z = 120

leg.IK()

print("Python IK for (-30, 150, 120):")
print("Coxa:", leg.a)
print("Femur:", leg.b)
print("Tibia:", leg.c)

leg.x = 0
leg.y = 180
leg.z = 100

leg.IK()

print("Python IK for (0, 180, 100):")
print("Coxa:", leg.a)
print("Femur:", leg.b)
print("Tibia:", leg.c)
