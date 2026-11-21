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
    retraceImages[0].texture = bigDigitTextures[tens];
    retraceImages[0].width = bigDigitWidths[tens];
    retraceImages[1].texture = bigDigitTextures[ones];
    retraceImages[1].width = bigDigitWidths[ones];
    return result;
}
