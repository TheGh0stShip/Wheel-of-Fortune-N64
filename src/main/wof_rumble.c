// wof_rumble.c -- the rumble thread and the messages that start, stop and reset a pak's motor
//
// StopMotor, ResetMotor and RumbleThread each end off an 8-byte boundary with the next function right
// after, which happens only inside an object: StopMotor to StartRumble are one object's. Whether
// StartMotor before it and ResetMotors after it are this object's too the text does not say.

#include "wof.h"
#include "rumble.h"

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

/*
=====================
RumbleThread

The rumble thread: carries out the motor messages.
=====================
*/
void RumbleThread(void *arg) {
    rumbleMsg_t *msg;
    s32 result;
    s32 index;
    s16 type;

    msg = 0;
    while (1) {
        osRecvMesg(&rumbleMsgQ, (OSMesg *)&msg, OS_MESG_BLOCK);
        LockSi();
        index = msg->index;
        type = msg->type;
        switch (type) {
        case 1:
            result = osMotorStart(&contPfs[index]);
            if (result == 0) {
                motorOn[index] = 1;
            }
            break;
        case 0:
            result = osMotorStop(&contPfs[index]);
            if (result == 0) {
                motorOn[index] = 0;
            }
            break;
        case 2:
            result = osMotorInit(&contMsgQ, &contPfs[index], index);
            result = osMotorStop(&contPfs[index]);
            if (result == 0) {
                motorOn[index] = 0;
            }
            break;
        }
        UnlockSi();
    }
}

/*
=====================
StartRumble

Rumbles a controller's pak for some frames at some strength.
=====================
*/
void StartRumble(s32 cont, s32 frames, f32 strength) {
    if (rumbles[cont].present == 0) {
        return;
    }
    rumbles[cont].frames = frames;
    rumbles[cont].strength = strength;
    rumbles[cont].level = 0;
}
