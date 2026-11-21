// idle.c -- guess: idle of the SDK demos. Starts the PI manager and the main and game threads, then
// idles at the lowest priority

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
