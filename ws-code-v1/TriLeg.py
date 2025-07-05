import maestro

ServoController = maestro.Controller('/dev/ttyAMA0')

print(f"servo maximum range: {ServoController.getMax()}")
print(f"servo minimum range: {ServoController.getMin()}")

class Trileg:
    def __init__(self, leg, sc, sf, st, coxa_deg, femur_deg, tibia_deg):
        self.leg = leg # name of the leg (e.g., 'L1', 'L2', 'L3, 'R1', 'R2', 'R3')
        self.sc = sc # servo pin for coxa
        self.sf = sf # servo pin for femur
        self.st = st # servo pin for tibia
        self.coxa_deg = coxa_deg
        self.femur_deg = femur_deg
        self.tibia_deg = tibia_deg
    
    def angleToDC(self):
        self.coxa_deg = int((100 * self.coxa_deg)/3 + 6000)
        self.femur_deg = int((100 * self.femur_deg)/3 + 6000)
        self.tibia_deg = int((100 * self.tibia_deg)/3 + 2000)
        print(f"coxa: {self.coxa_deg}")
        print(f"femur: {self.femur_deg}")
        print(f"tibia: {self.tibia_deg}")
    
    def move(self):
        self.angleToDC()
        ServoController.setTarget(self.sc, self.coxa_deg)
        ServoController.setTarget(self.sf, self.femur_deg)
        ServoController.setTarget(self.st, self.tibia_deg)

    def IK(self):
        pass