#include "wof.h"

/*
=====================
StopMotor

Asks the rumble thread to stop a pak's motor.
=====================
*/
void StopMotor(s32 cont) {
    rumbleMsg.type = 0;
    rumbleMsg.index = cont;
    osSendMesg(&rumbleMsgQ, (OSMesg)&rumbleMsg, OS_MESG_BLOCK);
}
