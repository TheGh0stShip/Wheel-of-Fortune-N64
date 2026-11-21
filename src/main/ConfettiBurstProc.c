// ConfettiBurstProc.c -- throws confetti for a while

#include "wof.h"


/*
=====================
ConfettiBurstProc

Throws confetti for a while.
=====================
*/
struct procResult_s ConfettiBurstProc(proc_t *proc) {
    struct procResult_s result;
    s32 event;
    s32 i;
    obj_t *obj;

    obj = proc->data->obj;
    for (;;) {
        event = ProcGetMessage(proc);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 8:
            proc->data->confettiBurst.countdown = 10;
            break;
        }
    }
    proc->data->confettiBurst.countdown--;
    if (proc->data->confettiBurst.countdown < 0) {
        if (proc->data->confettiBurst.countdown < -40) {
            result.w[1] = 0;
            result.w[0] = 1;
            return result;
        }
        if (proc->data->confettiBurst.countdown >= -9) {
            AddConfetti(80, 150, 60, 80, 30, 10, 2, 1);
        } else {
            AddConfetti(80, 150, 60, 80, 30, 10, 2, 1);
            result.w[1] = 1;
            result.w[0] = ((guRandom() % -1) * proc->data->confettiBurst.countdown) / frameRetraces;
            return result;
        }
    } else {
        i = 0;
        for (;;) {
            if (i >= 4) {
                break;
            }
            AddConfetti(52, 15, 27, 15, 300, 150, 6, 3);
            i++;
        }
    }
    result.w[1] = 1;
    result.w[0] = (guRandom() % 10) / frameRetraces;
    return result;
}
