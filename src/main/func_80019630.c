#include "wof.h"
#include "func_800051B4.h"


struct n64dk_r12 func_80019630(proc_t *proc) {
    struct n64dk_r12 ret;
    s32 task;
    s32 unused;  /* NOTE: unused in the original */
    s32 event;

    ret.w[1] = 1;
    ret.w[0] = 0;
    if (proc->unk_30->playerProc.player != D_800FB808) {
        func_8000AD9C(proc);
        return ret;
    }
    task = func_8000A990(0x5000000, -1);
    while ((event = func_8000ACE8(proc)) != 0) {
        switch (event) {
        case 8:
            func_80017C00(3, 0);
            func_8002EB40();
            ret.w[1] = 2;
            ret.w[0] = 5;
            break;
        case 5:
            func_80002CE0(D_800B9990[D_800FB808].unk_0FC + (D_800B61B5 - 'A'));
            func_8000AAB0(proc, 44, 0);
            ret.w[1] = 1;
            ret.w[0] = 30 / D_800B96B4;
            return ret;
        case 44:
            if (func_80007888(D_800B61B5, 2) > 0) {
                func_80007DAC(D_800B61B5);
                task = func_8000A56C(func_80010574, 0x1000000);
                ((proc_t *)task)->unk_30->playerProc.unk_10 = D_800B61B5;
                ret.w[1] = 2;
                ret.w[0] = 6;
            } else {
                func_80002CE0(1);
                func_800051B4(D_800B9990[D_800FB808].unk_014, 30, 0.8f);
                func_80017548();
                func_8000A850(31);
                func_8000AAB0(task, 31, 0);
                ret.w[1] = 0;
                ret.w[0] = 0;
                return ret;
            }
            break;
        case 6:
            func_80029974(0);
            func_8002FD50();
            task = func_8000A56C(func_8001933C, proc->unk_30->playerProc.player | 0x2000300);
            ((proc_t *)task)->unk_30->playerProc.player = proc->unk_30->playerProc.player;
            ret.w[1] = 2;
            ret.w[0] = 10;
            return ret;
        case 10:
            if (func_800088E4() != 1) {
                func_80017548();
            }
            func_8000A850(31);
            func_8000AAB0(task, 31, 0);
            ret.w[1] = 0;
            ret.w[0] = 0;
            return ret;
        case 34:
            ret.w[1] = 0;
            ret.w[0] = 0;
            return ret;
        }
    }
    return ret;
}
