// DemoTimerProc.c -- ends the demo after 30 seconds or on START

#include "wof.h"


/*
=====================
DemoTimerProc

Ends the demo after 30 seconds or on START.
=====================
*/
struct procResult_s DemoTimerProc(proc_t *proc) {
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
    now = (s32)(osGetTime() / osClockRate);
    if (((now - proc->data->timer.start) >= 30) || (((buttonsPressed & 0x1000) & 0xFFFF) != 0)) {
        ProcPostMessageClass(34, 0, 0, 1);
        result.w[1] = 0;
    }
    return result;
}
