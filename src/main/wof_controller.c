// wof_controller.c -- the controller thread, starting the controllers and the rumble, and reading the
// pads each frame
//
// ControllerThread and InitControllers end off an 8-byte boundary with the next function right after,
// which happens only inside an object: the three are one object's. The object's read-only data has no
// RCS run. Where it starts after __clearAudioDMA, and whether it runs on after ReadControllers into the
// rumble functions, the text does not say.

#include "wof.h"

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
