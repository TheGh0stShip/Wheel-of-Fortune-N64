// StartMotor.c -- asks the rumble thread to start a pak's motor

#include "wof.h"

/*
=====================
StartMotor

Asks the rumble thread to start a pak's motor.
=====================
*/
void StartMotor(s32 cont) {
    rumbleMsg.type = 1;
    rumbleMsg.index = cont;
    osSendMesg(&rumbleMsgQ, (OSMesg)&rumbleMsg, OS_MESG_BLOCK);
}
