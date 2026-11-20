#include "wof.h"

struct procResult_s func_8002BA44(proc_t *proc) {
    s32 event;
    s32 tens;
    s32 ones;
    struct procResult_s sp20;
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    sp20.w[1] = 1;
    sp20.w[0] = 0;
    while ((event = ProcGetMessage(proc)) != 0) {
        switch (event) {
        case 33:
            D_8005B2C0[0].unk_20 = D_8005B118[0];
            D_8005B2C0[0].width = D_8005B178[0];
            D_8005B2C0[1].unk_20 = D_8005B118[0];
            D_8005B2C0[1].width = D_8005B178[0];
            ProcPostMessage(proc, 31, 0);
            sp20.w[0] = 30 / frameRetraces;
            return sp20;
        case 31:
            sp20.w[1] = 0;
            sp20.w[0] = 1;
            return sp20;
        }
    }
    tens = bonusTimeLeft / 10;
    ones = bonusTimeLeft % 10;
    D_8005B2C0[0].unk_20 = D_8005B118[tens];
    D_8005B2C0[0].width = D_8005B178[tens];
    D_8005B2C0[1].unk_20 = D_8005B118[ones];
    D_8005B2C0[1].width = D_8005B178[ones];
    return sp20;
}
