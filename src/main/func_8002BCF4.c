#include "wof.h"

struct procResult_s func_8002BCF4(proc_t *proc) {
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
    D_8005B310[0].unk_20 = D_8005B118[tens];
    D_8005B310[0].width = D_8005B178[tens];
    D_8005B310[1].unk_20 = D_8005B118[ones];
    D_8005B310[1].width = D_8005B178[ones];
    return result;
}
