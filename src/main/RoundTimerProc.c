#include "wof.h"


struct procResult_s RoundTimerProc(proc_t *proc) {
    struct procResult_s result;
    OSTime time; /* NOTE: unused in the original. Eight bytes nothing touches; guess: an OSTime */
    s32 event;
    s32 now;
    s32 i;

    result.w[1] = 1;
    result.w[0] = 0;
    for (;;) {
        event = ProcGetMessage(proc);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 8:
            roundTime = 0;
            i = 0;
            for (;;) {
                if (i >= 3) {
                    break;
                }
                if (players[i].unk_014 == 4) {
                    roundTime = roundTime + 240;
                } else {
                    roundTime = roundTime + 300;
                }
                i++;
            }
        case 43:
            proc->data->timer.start = (s32)(osGetTime() / osClockRate);
            break;
        }
    }
    roundTime = roundTime + D_800BCA1C;
    now = (s32)(osGetTime() / osClockRate);
    if ((now - proc->data->timer.start) >= roundTime) {
        if (FindProc(0x5010000, -1) != 0) {
            return result;
        }
        if (FindProc(0x5020000, -1) != 0) {
            return result;
        }
        if (FindProc(0x2000100, 0xFF00FF00) != 0) {
            return result;
        }
        if (FindProc(0x2000200, 0xFF00FF00) != 0) {
            return result;
        }
        if (FindProc(0x2000300, 0xFF00FF00) != 0) {
            return result;
        }
        if (FindProc(0x2000500, 0xFF00FF00) != 0) {
            return result;
        }
        if (FindProc(0x7050000, 0xFF00FF00) != 0) {
            return result;
        }
        if (((f64)CheckPercentDone()) < 0.6) {
            PlaySound(3);
            CreatProc(FinalSpinProc, 0x7020000);
            ProcPostMessageClass(30, 0, 0, 0);
        }
        gameOver = 1;
        result.w[1] = 0;
        result.w[0] = 0;
        return result;
    }
    return result;
}
