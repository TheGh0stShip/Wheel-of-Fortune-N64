#include "wof.h"

void InitGame(void) {
    s32 count;

    osCreateMesgQueue(&dmaMessageQ, &dmaMessageBuf, 1);
    osCreateMesgQueue(&gfxMsgQ, gfxMsgBuf, 8);
    osCreateMesgQueue(&D_800B9CD0, D_800BEE00, 8);
    if (osTvType == 2) {
        osCreateScheduler(&sc, scheduleStack + OS_SC_STACKSIZE / sizeof(u64), 13, 30, 1);
    } else {
        osCreateScheduler(&sc, scheduleStack + OS_SC_STACKSIZE / sizeof(u64), 13, 2, 1);
    }
    osScAddClient(&sc, &gfxClient, &gfxMsgQ);
    osScAddClient(&sc, &D_800B3988, &D_800B9CD0);
    sched_cmdQ = osScGetCmdQ(&sc);
    count = (s32)osGetTime() & 4095;
    while (count-- > 0) {
        guRandom();
    }
    retraceTime = 0;
    minRetraces = 0;
    D_800B8294 = 0;
    retraceCount = 0;
    frameRetraces = 0;
    D_800BCD50 = 0;
    InitMemStack();
    InitControllers();
    InitAudio();
    InitGraphics();
    D_800BC6FC = 37;
    D_800B40C4 = 1;
    InitProcs();
    InitObjs();
    if (contPattern != 0) {
        StartLogos();
    } else {
        func_8000E738();
    }
    func_80026FD4();
}
