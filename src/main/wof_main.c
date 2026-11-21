// wof_main.c -- the boot, the idle thread, the frame, the main thread, the game thread, reading the
// cartridge and starting the game
//
// The object lies between the 4-byte gaps that end parse_args and InitGame. idle and RunFrame each end
// off an 8-byte boundary with the next function right after, which happens only inside an object.
// guess: the joins after boot, mainproc, GameThread and ReadRom, where nothing in the image decides and
// the project's ruling takes the join. Its text uses no read-only data.

#include "wof.h"

/*
=====================
boot

guess: boot of the SDK demos. Starts the OS and the idle thread.
=====================
*/
void boot(void) {
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    osInitialize();
    osCreateThread(&idleThread, 1, idle, (void *)bootArg, idleThreadStack + 0x2000 / sizeof(u64), 10);
    osStartThread(&idleThread);
}

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

/*
=====================
GameThread

The game thread: runs RunFrame forever.
=====================
*/
void GameThread(void *arg) {
    s32 zero;  /* NOTE: set to 0 and never read */

    zero = 0;
    while (1) {
        RunFrame();
    }
}

/*
=====================
ReadRom

Reads bytes from the cartridge by PI DMA and waits for them.
=====================
*/
void ReadRom(s32 rom, void *ram, s32 size) {
    OSIoMesg dmaIoMesgBuf;
    OSMesg dummyMesg;

    while (osPiGetStatus() == 1) {
    }
    osInvalICache(ram, size);
    osInvalDCache(ram, size);
    osPiStartDma(&dmaIoMesgBuf, OS_MESG_PRI_NORMAL, OS_READ, rom, ram, size, &dmaMessageQ);
    osRecvMesg(&dmaMessageQ, &dummyMesg, OS_MESG_BLOCK);
}

/*
=====================
InitGame

Creates the queues and the scheduler and starts memory, controllers, audio, graphics, procs and
objs.
=====================
*/
void InitGame(void) {
    s32 count;

    osCreateMesgQueue(&dmaMessageQ, &dmaMessageBuf, 1);
    osCreateMesgQueue(&gfxMsgQ, gfxMsgBuf, 8);
    osCreateMesgQueue(&retraceMsgQ, retraceMsgBuf, 8);
    if (osTvType == 2) {
        osCreateScheduler(&sc, scheduleStack + OS_SC_STACKSIZE / sizeof(u64), 13, 30, 1);
    } else {
        osCreateScheduler(&sc, scheduleStack + OS_SC_STACKSIZE / sizeof(u64), 13, 2, 1);
    }
    osScAddClient(&sc, &gfxClient, &gfxMsgQ);
    osScAddClient(&sc, &retraceClient, &retraceMsgQ);
    sched_cmdQ = osScGetCmdQ(&sc);
    count = (s32)osGetTime() & 4095;
    while (count-- > 0) {
        guRandom();
    }
    retraceTime = 0;
    minRetraces = 0;
    movieSound = 0;
    retraceCount = 0;
    frameRetraces = 0;
    initGameZero = 0;
    InitMemStack();
    InitControllers();
    InitAudio();
    InitGraphics();
    initGame37 = 37;
    movieDone = 1;
    InitProcs();
    InitObjs();
    if (contPattern != 0) {
        StartLogos();
    } else {
        ShowNoController();
    }
    InitOptions();
}
