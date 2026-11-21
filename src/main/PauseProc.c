// PauseProc.c -- sTART pauses and resumes; 30 seconds without a button in a game pause it too

#include "wof.h"

/*
=====================
PauseProc

START pauses and resumes; 30 seconds without a button in a game pause it too.
=====================
*/
struct procResult_s PauseProc(proc_t *proc) {
    struct procResult_s result;
    proc_t *task;
    s32 unused;  /* NOTE: unused in the original */
    s32 event;

    result.w[1] = 1;
    result.w[0] = 0;
    for (;;) {
        event = ProcGetMessage(proc);
        if (event == PRC_EVENT_NULL) {
            break;
        }
        switch (event) {
        case PRC_EVENT_INIT:
            lastInputTime = (s32)(osGetTime() / osClockRate);
        }
    }
    pausedTime = 0;
    if (gameMode == 2) {
        if (inputCount > 0) {
            lastInputTime = (s32)(osGetTime() / osClockRate);
            inputCount = 0;
        } else {
            if (((osGetTime() / osClockRate) - lastInputTime) > 30) {
                PauseGame();
                return result;
            }
        }
    } else {
        if (gameMode == 8) {
            if (((buttonsPressed & 0xB000) & 0xFFFF) != 0) {
                task = FindProc(0x6060000, -1);
                if (task != 0) {
                    ProcPostMessage(task, PRC_EVENT_GAME_OVER, 1);
                }
            }
            return result;
        }
    }
    if (((buttonsPressed & 0x1000) & 0xFFFF) != 0) {
        if (gameMode != 6) {
            PauseGame();
        } else {
            FreeObjClass(0x5020000, -1);
            gameMode = pausedMode;
            ResumeSounds();
            pausedTime = ((s32)(osGetTime() / osClockRate)) - pauseStart;
            lastInputTime = (s32)(osGetTime() / osClockRate);
        }
    }
    return result;
}
