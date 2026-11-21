#include "wof.h"

/*
=====================
PauseProc

START pauses and resumes; 30 seconds without a button in a game pause it too.
=====================
*/
struct procResult_s PauseProc(proc_t *proc) {
    struct procResult_s sp10;
    proc_t *sp20;
    s32 unused;  /* NOTE: unused in the original */
    s32 sp28;

    sp10.w[1] = 1;
    sp10.w[0] = 0;
    for (;;) {
        sp28 = ProcGetMessage(proc);
        if (sp28 == 0) {
            break;
        }
        switch (sp28) {
        case 8:
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
                return sp10;
            }
        }
    } else {
        if (gameMode == 8) {
            if (((buttonsPressed & 0xB000) & 0xFFFF) != 0) {
                sp20 = FindProc(0x6060000, -1);
                if (sp20 != 0) {
                    ProcPostMessage(sp20, 46, 1);
                }
            }
            return sp10;
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
    return sp10;
}
