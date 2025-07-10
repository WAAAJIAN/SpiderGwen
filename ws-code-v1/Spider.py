from TriLeg import Trileg
import time

class Spider:
    def _init__(self):
        self.L1 = Trileg('L1', 
                         sc= 0, sf= 1, st= 2, 
                         coxa_deg= 0, femur_deg= 0, tibia_deg= 0)
        self.L2 = Trileg('L2', 
                         sc= 3, sf= 4, st= 5, 
                         coxa_deg= 0, femur_deg= 0, tibia_deg= 0)
        self.L3 = Trileg('L3', 
                         sc= 6, sf= 7, st= 8, 
                         coxa_deg= 0, femur_deg= 0, tibia_deg= 0)
        self.R1 = Trileg('R1', 
                         sc= 21, sf= 22, st= 23, 
                         coxa_deg= 0, femur_deg= 0, tibia_deg= 0)
        self.R2 = Trileg('R2', 
                         sc= 18, sf= 19, st= 20, 
                         coxa_deg= 0, femur_deg= 0, tibia_deg= 0)
        self.R3 = Trileg('R3', 
                         sc= 9, sf= 10, st= 11, 
                         coxa_deg= 0, femur_deg= 0, tibia_deg= 0)
        
    ''' gait motion code here '''

def main():
    gwen = Spider()

    Spider.L1.move()
    Spider.L1.clean()
    time.sleep(1)

    Spider.L2.move()
    Spider.L2.clean()
    time.sleep(1)

    Spider.L3.move()
    Spider.L3.clean()
    time.sleep(1)

    Spider.R1.move()
    Spider.R1.clean()
    time.sleep(1)  

    Spider.R2.move()
    Spider.R2.clean()
    time.sleep(1)
    
    Spider.R3.move()
    Spider.R3.clean()

main()