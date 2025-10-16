from spider import *

def main():
    gwen = Spider()
    try:
        # sleep(2)
        # gwen.balance()
        while(1):
            inp = input("enter: ")
            if inp[0] == 'w' : gwen.walkCycle(int(inp[1:]), [0,1])
            elif inp[0] == 'd' : gwen.walkCycle(int(inp[1:]), [1,0])
            elif inp[0] == 's' : gwen.walkCycle(int(inp[1:]), [0,-1])
            elif inp[0] == 'a' : gwen.walkCycle(int(inp[1:]), [-1,0])
            elif inp[0] == 'e' : gwen.walkCycle(int(inp[1:]), polarVector(45))
            elif inp[0] == 'q' : gwen.walkCycle(int(inp[1:]), polarVector(135))
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