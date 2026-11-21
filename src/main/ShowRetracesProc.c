// ShowRetracesProc.c -- shows frameRetraces as two digits

#include "wof.h"

/*
=====================
ShowRetracesProc

Shows frameRetraces as two digits.
=====================
*/
struct procResult_s ShowRetracesProc(proc_t *proc) {
    s32 busy;
    s32 tens;
    s32 ones;
    struct procResult_s result;
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    result.w[1] = 1;
    result.w[0] = 0;
    do {
        busy = ProcGetMessage(proc);
    } while (busy != 0);
    tens = frameRetraces / 10;
    ones = frameRetraces % 10;
    D_8005B310[0].texture = D_8005B118[tens];
    D_8005B310[0].width = D_8005B178[tens];
    D_8005B310[1].texture = D_8005B118[ones];
    D_8005B310[1].width = D_8005B178[ones];
    return result;
}
