#include "wof.h"

struct procResult_s func_8002B730(proc_t *proc) {
    s32 event;
    struct procResult_s ret;
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    ret.w[1] = 1;
    ret.w[0] = 0;
    while ((event = ProcGetMessage(proc)) != 0) {
        switch (event) {
        case 8:
            gameMode = 8;
            func_8002A538();
            func_80027218(proc, 0, func_80027F3C, 0x5050100);
            D_800B96A8++;
            ret.w[0] = 30 / frameRetraces;
            return ret;
        case 46:
            CreatProc(func_8002B318, 0x6060000);
            ret.w[1] = 0;
            ret.w[0] = 0;
            return ret;
        }
    }
    func_80021B04(0, 46);
    ret.w[1] = 2;
    ret.w[0] = 46;
    return ret;
}
