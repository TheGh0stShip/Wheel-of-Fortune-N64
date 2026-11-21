// wof_timers.c -- the timers of a round, of the demo and of a solve
//
// RoundTimerProc and DemoTimerProc each end off an 8-byte boundary with the next function right after,
// which happens only inside an object. Whether FinalSpinProc before it and func_8002FB60 after it are
// this object's the text does not say.

#include "wof.h"

/*
=====================
RoundTimerProc

The time of a round, 300 seconds a person and 240 the machine; then the final spin or the end.
=====================
*/
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
                if (players[i].controller == 4) {
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
    roundTime = roundTime + pausedTime;
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

/*
=====================
SolveTimerProc

The time to solve: 8 seconds, or 20 in the bonus round; then it posts message 33.
=====================
*/
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
    proc->data->timer.start = proc->data->timer.start + pausedTime;
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
