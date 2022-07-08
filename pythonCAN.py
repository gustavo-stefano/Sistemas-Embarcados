import can 
import time

bus = can.interface.Bus(channel='can1', bustype='socketcan_ctypes')#initializing the can bus interface

#the pre-defined message id's 
#------board 1----
fwd1 = 1300 #foward board 1
bwd1 = 1301 #backward board 1

#------board 2----
fwd2 = 1302 #foward board 2
bwd2 = 1303 #backward board2
stnd = 1304 #standBy ...
#============================


#------command options-------
drive = 1 #command for walk
reverse = 2 #... for reverse
neutral = 3 # do nothing
left = 4 #turn left
right = 5 #turn right
exit = 6
#============================

msg_id1 = 0
msg_id2 = 0

cont = [] #no content need to be send


running = True

#instruction messages
msg1 = can.Message(arbitration_id = msg_id1, data = cont)
msg2 = can.Message(arbitration_id = msg_id2, data = cont)

while running:
    if cmd == drive:
    	#both controllers runs foward routine
        msg_id1 = fwd1
        msg_id2 = fwd2

        bus.send(msg1)#send message
        bus.send(msg2)
        print("drive message was send")
    elif cmd == reverse:
    	#both controllers runs backward routine
        msg_id1 = bwd1
        msg_id2 = bwd2

        bus.send(msg1)
        bus.send(msg2)
        print("reverse message was send")
    elif cmd == left:
    	#Controller 1 runs foward routine
    	#Controller 2 runs backward routine
    	#This results on a turn left routine
        msg_id1 = fwd1
        msg_id2 = bwd2

        bus.send(msg1)
        bus.send(msg2)

        print("left message was send")
    elif cmd == right:
    	#Controller 1 runs backward routine
    	#Controller 2 runs foward routine
    	#This results on a turn right routine
        msg_id1 = bwd1
        msg_id2 = fwd2

        bus.send(msg1)
        bus.send(msg2)

        print("right message was send")
    elif cmd == neutral:
    	#Controller 1 runs standBy mode
        msg_id1 = stnd
        
        bus.send(msg1)
        print("stand by message was send")

    elif cmd == exit:
         running = False


print("Bye bye :)")


