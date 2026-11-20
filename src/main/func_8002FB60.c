#include "wof.h"


struct procResult_s func_8002FB60(proc_t *proc) {
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
    if ((now - proc->data->timer.start) >= 5) {
        ProcPostEvent(48);
        result.w[1] = 0;
    }
    return result;
}
