#include "wof.h"


struct n64dk_r12 func_8001C584(proc_t *proc) {
    s32 event;
    struct n64dk_r12 ret;
    s32 task;

    ret.w[1] = 1;
    ret.w[0] = 0;
    if (proc->unk_30->playerProc.player != D_800FB808) {
        while ((event = func_8000ACE8(proc)) != 0) {
            switch (event) {
            case 34:
                ret.w[1] = 0;
                ret.w[0] = 0;
                return ret;
            case 42:
                ret.w[1] = 0;
                ret.w[0] = 0;
                return ret;
            }
        }
        return ret;
    }
    while ((event = func_8000ACE8(proc)) != 0) {
        switch (event) {
        case 38:
            func_80002CE0(D_800B9990[D_800FB808].unk_10C);
            D_800B9990[D_800FB808].unk_008 = 0;
            /* fallthrough */
        case 3:
        case 9:
        case 10:
        case 31:
            func_80017C00(3, 1);
            task = func_8000A990(0x5000000, -1);
            func_8000AAB0(task, 24, 0);
            if (func_80007EEC(1) == 1) {
                func_8000AAB0(task, 21, 0);
                func_80016008();
                D_800B96A8 += 3;
                func_80002CE0(5);
                task = func_8000A56C(func_80017DBC, proc->unk_30->playerProc.player | 0x2000500);
                ((proc_t *)task)->unk_30->playerProc.player = proc->unk_30->playerProc.player;
                if (D_800B9CF0 != 0 || D_800B619C == D_800B96C0 - 1) {
                    ret.w[1] = 0;
                    ret.w[0] = 0;
                } else {
                    ret.w[1] = 2;
                    ret.w[0] = 39;
                }
                return ret;
            }
            if (D_800BEE54 == 0 && func_800082E4() == 2) {
                D_800BEE54 = 1;
                func_80002CE0(6);
            }
            func_8000AAB0(proc, 28, 0);
            ret.w[1] = 1;
            ret.w[0] = 20 / D_800B96B4;
            return ret;
        case 8:
            ret.w[1] = 2;
            ret.w[0] = 40;
            return ret;
        case 40:
            func_80015D4C();
            func_8000AAB0(proc, 1, 0);
            func_80017C00(3, 1);
            ret.w[1] = 1;
            ret.w[0] = 60 / D_800B96B4;
            return ret;
        case 1:
        case 32:
            func_8000A850(24);
            if (D_800BCA00 == 1) {
                task = func_8000A56C(func_8001BED8, proc->unk_30->playerProc.player | 0x2030400);
                ((proc_t *)task)->unk_30->playerProc.player = proc->unk_30->playerProc.player;
                ((proc_t *)task)->unk_30->playerProc.unk_0C = proc->unk_30->playerProc.unk_0C;
                ret.w[1] = 2;
                ret.w[0] = 31;
                return ret;
            }
            func_8000AAB0(proc, 28, 0);
            ret.w[1] = 1;
            ret.w[0] = 30 / D_800B96B4;
            func_80017C00(3, 1);
            D_800B96A8++;
            return ret;
        case 15:
            func_8000A850(24);
            if (D_800BCA00 == 1) {
                task = func_8000A56C(func_8001BED8, proc->unk_30->playerProc.player | 0x2030400);
                ((proc_t *)task)->unk_30->playerProc.player = proc->unk_30->playerProc.player;
                ((proc_t *)task)->unk_30->playerProc.unk_0C = proc->unk_30->playerProc.unk_0C;
                ret.w[1] = 2;
                ret.w[0] = 31;
                return ret;
            }
            func_8000AAB0(proc, 12, 0);
            ret.w[1] = 1;
            ret.w[0] = 60 / D_800B96B4;
            func_80017C00(3, 1);
            return ret;
        case 28:
            if (D_800BCA00 == 1) {
                task = func_8000A56C(func_8001BED8, proc->unk_30->playerProc.player | 0x2030400);
                ((proc_t *)task)->unk_30->playerProc.player = proc->unk_30->playerProc.player;
                ((proc_t *)task)->unk_30->playerProc.unk_0C = proc->unk_30->playerProc.unk_0C;
                ret.w[1] = 2;
                ret.w[0] = 31;
                return ret;
            }
            func_8001AA60(proc);
            ret.w[1] = 1;
            ret.w[0] = 60 / D_800B96B4;
            return ret;
        case 12:
            if (guRandom() % 100 < 33) {
                func_80002CE0(D_800B9990[D_800FB808].unk_100);
            }
            D_800B96A0 = 0;
            task = func_8000A990(0x5000000, -1);
            func_8000AAB0(task, 23, 0);
            task = func_8000A56C(func_8001AE18, proc->unk_30->playerProc.player | 0x2000100);
            ((proc_t *)task)->unk_30->playerProc.player = proc->unk_30->playerProc.player;
            ((proc_t *)task)->unk_30->playerProc.unk_0C = proc->unk_30->playerProc.unk_0C;
            ret.w[1] = 2;
            ret.w[0] = 3;
            return ret;
        case 13:
            func_80002CE0(D_800B9990[D_800FB808].unk_104);
            D_800B96A0 = 0;
            task = func_8000A990(0x5000000, -1);
            func_8000AAB0(task, 23, 0);
            task = func_8000A56C(func_8001B6BC, proc->unk_30->playerProc.player | 0x2000200);
            ((proc_t *)task)->unk_30->playerProc.player = proc->unk_30->playerProc.player;
            ((proc_t *)task)->unk_30->playerProc.unk_0C = proc->unk_30->playerProc.unk_0C;
            ret.w[1] = 2;
            ret.w[0] = 9;
            return ret;
        case 14:
            func_80002CE0(D_800B9990[D_800FB808].unk_108);
            task = func_8000A990(0x5000000, -1);
            func_8000AAB0(task, 23, 0);
            task = func_8000A56C(func_8001BC44, proc->unk_30->playerProc.player | 0x2000300);
            ((proc_t *)task)->unk_30->playerProc.player = proc->unk_30->playerProc.player;
            ((proc_t *)task)->unk_30->playerProc.unk_0C = proc->unk_30->playerProc.unk_0C;
            ret.w[1] = 2;
            ret.w[0] = 10;
            return ret;
        case 37:
            D_800B96A0 = 0;
            task = func_8000A990(0x5000000, -1);
            D_800B61B5 = '3';
            func_8000AAB0(task, 27, 1);
            func_8000AAB0(proc, 38, 0);
            ret.w[1] = 1;
            ret.w[0] = 60 / D_800B96B4;
            return ret;
        case 39:
            func_800177A4();
            if (proc->unk_30->playerProc.player != D_800FB808) {
                ret.w[1] = 2;
                ret.w[0] = -1;
            } else {
                ret.w[1] = 1;
                ret.w[0] = 0;
            }
            return ret;
        case 30:
            ret.w[1] = 2;
            ret.w[0] = 32;
            return ret;
        case 34:
            ret.w[1] = 0;
            ret.w[0] = 0;
            return ret;
        }
    }
    return ret;
}
