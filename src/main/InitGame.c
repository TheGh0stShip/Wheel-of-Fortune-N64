// InitGame.c -- creates the queues and the scheduler and starts memory, controllers, audio,
// graphics, procs and objs

#include "wof.h"

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
    D_800BCD50 = 0;
    InitMemStack();
    InitControllers();
    InitAudio();
    InitGraphics();
    D_800BC6FC = 37;
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
