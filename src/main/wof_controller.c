// wof_controller.c -- the controllers and the rumble: the controller thread, starting the controllers,
// the rumble thread and its motor messages, and reading the pads each frame
//
// ControllerThread, InitControllers, StopMotor, ResetMotor and RumbleThread each end off an 8-byte
// boundary with the next function right after, which happens only inside an object. guess: the joins
// after ReadControllers, StartMotor and StartRumble, and the boundary after ResetMotors. The RCS run at
// 0x800004F0 opens the read-only data of an object starting after one of ReadControllers, StartMotor,
// StartRumble and ResetMotors; under the project's ruling every other open position is a join, and the
// boundary goes after ResetMotors because the call graph ties the rumble to the controllers
// (InitControllers starts RumbleThread, ReadControllers calls StartMotor and StopMotor) and not to the
// graphics after it. Where the object starts after __clearAudioDMA rests on the lineage of the audio
// manager before it, whose file ends there. The object's read-only data has no RCS run.

#include "wof.h"
#include "rumble.h"

/*
=====================
ControllerThread

The controller thread: on each SI event of a read it started, ReadControllers.
=====================
*/
void ControllerThread(void *arg) {
    OSScMsg *msg;

    msg = 0;
    while (1) {
        osRecvMesg(&contMsgQ, (OSMesg *)&msg, OS_MESG_BLOCK);
        switch (msg->type) {
        case 5:
            if (contReading != 0) {
                UnlockSi();
                ReadControllers();
                contReading = 0;
            }
            break;
        }
    }
}

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

/*
=====================
ReadControllers

Reads the pads, runs the rumble, counts presses and gives the game its buttons.
=====================
*/
void ReadControllers(void) {
    OSContPad *pad;
    u16 i;
    s32 j;
    u16 buttons;
    u16 one;  /* NOTE: set to 1 and never read */

    one = 1;
    osContGetReadData(contPads);
    i = 0;
    while (i < 4) {
        if ((contPattern >> i) % 2 != 0) {
            pad = &contPads[i];
            switch (pad->errno) {
            case 0:
                if (rumbles[i].present != 0) {
                    if (rumbles[i].frames > 0) {
                        rumbles[i].frames--;
                        rumbles[i].level += rumbles[i].strength;
                        if ((f64)rumbles[i].level < 1.0) {
                            StopMotor(i);
                        } else {
                            rumbles[i].level = (f32)((f64)rumbles[i].level - 1.0);
                            StartMotor(i);
                        }
                    } else if (motorOn[i] != 0) {
                        StopMotor(i);
                    }
                }
                buttons = pad->button;
                j = 0;
                while (j < 16) {
                    if ((buttons & 1) != 0) {
                        if (buttonUpFrames[i][j] < 5) {
                            buttonUpFrames[i][j] = 0;
                        } else {
                            contPressed[i] |= 1 << j;
                            buttonUpFrames[i][j] = 0;
                        }
                    } else if (buttonUpFrames[i][j] < 6) {
                        buttonUpFrames[i][j]++;
                    }
                    buttons >>= 1;
                    j++;
                }
            }
        }
        i++;
    }
    if (newFrame != 0) {
        if (gameMode == 3 || gameMode == 1 || gameMode == 7 || gameMode == 8) {
            playerPad.stick_x = 0;
            playerPad.stick_y = 0;
            buttonsPressed = 0;
            i = 0;
            while (i < 4) {
                buttonsPressed |= contPressed[i];
                if ((contPattern >> i) % 2 != 0) {
                    if (contPads[i].stick_x >= 41 || contPads[i].stick_x < -40) {
                        playerPad.stick_x = contPads[i].stick_x;
                    }
                    if (contPads[i].stick_y >= 41 || contPads[i].stick_y < -40) {
                        playerPad.stick_y = contPads[i].stick_y;
                    }
                }
                i++;
            }
        } else if (gameMode == 6 || players[curPlayer].controller == 4) {
            buttonsPressed = 0;
            i = 0;
            while (i < 4) {
                buttonsPressed = (contPressed[i] & 0x1000) | buttonsPressed;
                i++;
            }
        } else {
            buttonsPressed = contPressed[players[curPlayer].controller];
            playerPad = contPads[players[curPlayer].controller];
        }
        i = 0;
        while (i < 4) {
            contPressed[i] = 0;
            i++;
        }
        newFrame = 0;
    }
}

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

/*
=====================
ResetMotors

ResetMotor on each controller that has a rumble pak.
=====================
*/
void ResetMotors(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if ((contPattern >> i) % 2 != 0) {
            if (rumbles[i].present != 0) {
                ResetMotor(i);
            }
        }
    }
}
