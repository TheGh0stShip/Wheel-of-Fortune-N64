// wof_main.c -- the idle thread, the frame and the main thread
//
// idle and RunFrame each end off an 8-byte boundary with the next function right after, which happens
// only inside an object: idle to mainproc are one object's. Whether boot before it and GameThread and
// ReadRom after it are this object's too the text does not say.

#include "wof.h"

/*
=====================
idle

guess: idle of the SDK demos. Starts the PI manager and the main and game threads, then idles at the
lowest priority.
=====================
*/
void idle(void *arg) {
    osCreatePiManager(OS_PRIORITY_PIMGR, &PiMessageQ, PiMessages, 200);
    osCreateThread(&mainThread, 10, mainproc, arg, mainThreadStack + 0x2000 / sizeof(u64), 10);
    osCreateThread(&gameThread, 11, GameThread, arg, gameThreadStack + 0x2000 / sizeof(u64), 8);
    if (debugflag == 0) {
        osStartThread(&mainThread);
    }
    osSetThreadPri(0, 0);
loop_3:
    goto loop_3;
}

/*
=====================
RunFrame

Waits for the retraces of a frame, runs DoProcs and sends the frame's graphics task.
=====================
*/
void RunFrame(void) {
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    while (pendingGfx < 2 && newFrame == 0) {
        while (minRetraces > retraceCount) {
        }
        frameRetraces = retraceCount;
        retraceCount = 0;
        if (frameRetraces == 0) {
            frameRetraces = 1;
        }
        DoProcs();
        newFrame = 1;
        createGfxTask(&gfxInfo[curGfxInfo]);
        pendingGfx++;
        curGfxInfo ^= 1;
    }
}

/*
=====================
mainproc

guess: mainproc of the SDK demos, the main thread. Starts the game, then handles the scheduler's
messages: on each retrace it starts a controller read, on each finished graphics task it plays
movieSound, and on the pre-NMI it stops the rumble.
=====================
*/
void mainproc(void *arg) {
    OSScMsg *msg;

    msg = 0;
    curGfxInfo = 0;
    pendingGfx = 0;
    contReading = 0;
    InitGame();
    osStartThread(&gameThread);
    while (1) {
        osRecvMesg(&gfxMsgQ, (OSMesg *)&msg, OS_MESG_BLOCK);
        switch (msg->type) {
        case OS_SC_RETRACE_MSG:
            retraceCount++;
            retraceTime++;
            if (contPattern != 0 && contReading == 0) {
                contReading = 1;
                LockSi();
                osContStartReadData(&contMsgQ);
            } else if (contPattern == 0) {
                newFrame = 0;
            }
            break;
        case OS_SC_DONE_MSG:
            pendingGfx--;
            if (movieSound != 0) {
                movieSoundSlot = PlaySound(movieSound);
                movieSound = 0;
            }
            break;
        case OS_SC_PRE_NMI_MSG:
            pendingGfx += 2;
            ResetMotors();
            break;
        }
    }
}
