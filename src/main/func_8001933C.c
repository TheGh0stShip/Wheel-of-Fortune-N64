#include "wof.h"
#include "rumble.h"


struct procResult_s func_8001933C(proc_t *proc) {
    struct procResult_s ret;
    proc_t *task;
    s32 unused;  /* NOTE: unused in the original */
    s32 event;

    ret.w[1] = 1;
    ret.w[0] = 0;
    if (proc->data->playerProc.player != D_800FB808) {
        ProcClearMessages(proc);
        return ret;
    }
    task = FindProc(0x1020000, -1);
    while ((event = ProcGetMessage(proc)) != 0) {
        switch (event) {
        case 8:
            func_8002EBF4();
            func_80017C00(3, 0);
            ret.w[1] = 2;
            ret.w[0] = 5;
            return ret;
        case 5:
            if (func_800088E4() == 1) {
                D_800B96A8 = D_800B96A8 + 2;
                ProcPostMessage(task, 19, 0);
                ProcPostEvent(10);
                ret.w[1] = 0;
                ret.w[0] = 0;
            } else {
                ProcPostMessage(task, 20, 0);
                PlaySound(1);
                StartRumble(D_800B9990[D_800FB808].unk_014, 30, 0.8f);
                if (D_800BCA00 == 0) {
                    if (func_80017548() != 0) {
                        ProcPostEvent(10);
                    }
                } else {
                    ProcPostEvent(10);
                }
                ret.w[1] = 0;
                ret.w[0] = 0;
                return ret;
            }
            break;
        case 34:
            ret.w[1] = 0;
            ret.w[0] = 0;
            return ret;
        }
    }
    return ret;
}
