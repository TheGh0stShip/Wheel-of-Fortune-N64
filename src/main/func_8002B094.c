#include "wof.h"

struct procResult_s func_8002B094(proc_t *proc) {
    s32 event;
    struct procResult_s result;
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    result.w[1] = 1;
    result.w[0] = 0;
    while ((event = ProcGetMessage(proc)) != 0) {
        switch (event) {
        case 8:
            D_800BCD54 = 8;
            func_8002A538();
            func_80027218(proc, 0, func_80027F3C, 0x5050100);
            D_800B96A8 += 2;
            result.w[0] = 30 / frameRetraces;
            return result;
        case 46:
            StopAllSounds();
            result.w[1] = 1;
            result.w[0] = 2;
            FreeObjClass(0x1000000, 0xFF000000);
            FreeObjClass(0xA000000, 0xFF000000);
            FreeObjClass(0x4000000, 0xFF000000);
            ProcPostMessage(proc, 35, 0);
            return result;
        case 35:
            KillOtherProcs(proc);
            InitObjs();
            func_80021E28();
            func_8000E794();
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        }
    }
    func_80021B04(0, 46);
    result.w[1] = 2;
    result.w[0] = 46;
    return result;
}
