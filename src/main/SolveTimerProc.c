#include "wof.h"


struct procResult_s SolveTimerProc(proc_t *proc) {
    struct procResult_s result;
    OSTime time; /* NOTE: unused in the original. Eight bytes nothing touches; guess: an OSTime */
    s32 event;
    s32 now;

    result.w[1] = 1;
    result.w[0] = 0;
    for (;;) {
        event = ProcGetMessage(proc);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 8:
            proc->data->timer.start = (s32)(osGetTime() / osClockRate);
            break;
        }
    }
    proc->data->timer.start = proc->data->timer.start + D_800BCA1C;
    now = (s32)(osGetTime() / osClockRate);
    if (gameMode == 4) {
        bonusTimeLeft = 20 - (now - proc->data->timer.start);
        if ((now - proc->data->timer.start) >= 20) {
            bonusTimeLeft = 0;
            ProcPostMessageClass(33, 0, 0, 0);
            result.w[1] = 0;
        }
    } else {
        if ((now - proc->data->timer.start) >= 8) {
            ProcPostMessageClass(33, 0, 0, 0);
            ProcPostEvent(33);
            result.w[1] = 0;
        }
    }
    return result;
}
