// RunFrame.c -- waits for the retraces of a frame, runs DoProcs and sends the frame's graphics task

#include "wof.h"

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
