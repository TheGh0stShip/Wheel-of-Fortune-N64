#include "wof.h"


struct procResult_s func_8002BE84(proc_t *proc) {
    s32 event;
    struct procResult_s sp18;
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    sp18.w[1] = 1;
    sp18.w[0] = 0;
    while ((event = ProcGetMessage(proc)) != 0) {
        switch (event) {
        case 8:
            D_800B96A8 = D_800B96A8 + 6;
            func_80032AD4(1);
            func_80016008();
            func_80034950();
            KillProcClass(0x5050200, -1, 1);
            D_800B9990[D_800FB808].unk_004 = D_800B9990[D_800FB808].unk_004 + 0x61A8;
            PlaySound(5);
            func_80027218(proc, 0, func_8002842C, 0x5050000);
            sp18.w[0] = 320 / frameRetraces;
            return sp18;
        }
    }
    func_80016B9C(20);
    CreatProc(func_8002B730, 0x6000000);
    sp18.w[1] = 0;
    sp18.w[0] = 1;
    return sp18;
}
