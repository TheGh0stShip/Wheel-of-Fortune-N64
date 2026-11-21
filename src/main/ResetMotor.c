#include "wof.h"

/*
=====================
ResetMotor

Asks the rumble thread to start a pak over (osMotorInit, then stop)
=====================
*/
void ResetMotor(s32 cont) {
    rumbleMsg.type = 2;
    rumbleMsg.index = cont;
    osSendMesg(&rumbleMsgQ, (OSMesg)&rumbleMsg, OS_MESG_BLOCK);
}
