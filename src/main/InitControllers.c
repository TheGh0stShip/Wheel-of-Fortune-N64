// InitControllers.c -- starts the rumble and controller threads and the controllers, and the motor
// of each rumble pak found; "Failure initing controllers" if osContInit fails

#include "wof.h"


/*
=====================
InitControllers

Starts the rumble and controller threads and the controllers, and the motor of each rumble pak
found; "Failure initing controllers" if osContInit fails.
=====================
*/
void InitControllers(void) {
    s32 i;
    s32 j;
    s32 result;

    contPattern = 0;
    osCreateMesgQueue(&rumbleMsgQ, &rumbleMsgBuf, 1);
    osCreateThread(&rumbleThread, 8, RumbleThread, 0, (void *)(rumbleThreadStack + 0x2000 / sizeof(u64)), 10);
    osStartThread(&rumbleThread);
    for (i = 0; i < 4; i++) {
        rumbles[i].present = 0;
    }
    osCreateMesgQueue(&contMsgQ, &contMsgBuf, 1);
    osCreateThread(&contThread, 9, ControllerThread, 0, (void *)(contThreadStack + 0x2000 / sizeof(u64)), 9);
    contEventMsg.type = 5;
    osSetEventMesg(OS_EVENT_SI, &contMsgQ, (OSMesg)&contEventMsg);
    if ((i = (s32)osContInit(&contMsgQ, &contPattern, contStatus)) != 0) {
        PrintStr("Failure initing controllers\n");
    }
    i = 0;
    while (i < 4) {
        if ((contPattern >> i) % 2 != 0) {
            if ((contStatus[i].type & 4) != 0) {
                if ((contStatus[i].status & 1) != 0) {
                    result = osPfsInit(&contMsgQ, &contPfs[i], i);
                    if (result == 10 || result == 11) {
                        result = osMotorInit(&contMsgQ, &contPfs[i], i);
                        if (result == 0) {
                            rumbles[i].present = 1;
                            StopMotor(i);
                        } else {
                            // NOTE: empty in retail, a branch over nothing; guess: a debug message, compiled out
                        }
                    } else if (result == 0) {
                        // NOTE: empty in retail, a branch over nothing; guess: a debug message, compiled out
                    }
                }
            }
        }
        contPressed[i] = 0;
        for (j = 0; j < 16; j++) {
            buttonUpFrames[i][j] = 0;
        }
        i++;
    }
    newFrame = 0;
    osStartThread(&contThread);
}
