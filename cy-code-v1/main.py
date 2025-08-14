from spider import *

def main():
    gwen = Spider()
    try:
        # sleep(2)
        # gwen.balance()
        while(1):
            inp = input("enter: ")
            if inp == 'w' : gwen.gaitFunction[gwen.gait]([0,1])
        #     elif inp == 'd' : gwen.gaitFunction[gwen.gait]([1,0])
            elif inp == 's' : gwen.gaitFunction[gwen.gait]([0,-1])
        #     elif inp == 'a' : gwen.gaitFunction[gwen.gait]([-1,0])
        #     elif inp == 'e' : gwen.gaitFunction[gwen.gait](polarVector(45))
        #     elif inp == 'q' : gwen.gaitFunction[gwen.gait](polarVector(135))
            elif inp == '0' : gwen.gaitChange(0)
            elif inp == '1' : gwen.gaitChange(1)
            elif inp == '2' : gwen.gaitChange(2)
            elif inp == '3' : gwen.gaitChange(3)
            elif inp == '4' : gwen.gaitChange(4)

            # angle = int(input("enter angle:"))
            # gwen.rotate_x(angle)
        # j = -30
        # for i in range(60):
        #     gwen.rotate_x(j+i)

    except KeyboardInterrupt:
        print("Stopping Spider.....")
        gwen.stop_leg()

if __name__ == "__main__":
    main()