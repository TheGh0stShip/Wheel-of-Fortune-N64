#include "wof.h"
#include "rumble.h"


struct procResult_s func_80019630(proc_t *proc) {
    struct procResult_s ret;
    proc_t *task;
    s32 unused;  /* NOTE: unused in the original */
    s32 event;

    ret.w[1] = 1;
    ret.w[0] = 0;
    if (proc->unk_30->playerProc.player != D_800FB808) {
        ProcClearMessages(proc);
        return ret;
    }
    task = FindProc(0x5000000, -1);
    while ((event = ProcGetMessage(proc)) != 0) {
        switch (event) {
        case 8:
            func_80017C00(3, 0);
            func_8002EB40();
            ret.w[1] = 2;
            ret.w[0] = 5;
            break;
        case 5:
            PlaySound(D_800B9990[D_800FB808].unk_0FC + (D_800B61B5 - 'A'));
            ProcPostMessage(proc, 44, 0);
            ret.w[1] = 1;
            ret.w[0] = 30 / frameRetraces;
            return ret;
        case 44:
            if (func_80007888(D_800B61B5, 2) > 0) {
                func_80007DAC(D_800B61B5);
                task = CreatProc(func_80010574, 0x1000000);
                task->unk_30->data80010574.letter = D_800B61B5;
                ret.w[1] = 2;
                ret.w[0] = 6;
            } else {
                PlaySound(1);
                StartRumble(D_800B9990[D_800FB808].unk_014, 30, 0.8f);
                func_80017548();
                ProcPostEvent(31);
                ProcPostMessage(task, 31, 0);
                ret.w[1] = 0;
                ret.w[0] = 0;
                return ret;
            }
            break;
        case 6:
            func_80029974(0);
            func_8002FD50();
            task = CreatProc(func_8001933C, proc->unk_30->playerProc.player | 0x2000300);
            task->unk_30->playerProc.player = proc->unk_30->playerProc.player;
            ret.w[1] = 2;
            ret.w[0] = 10;
            return ret;
        case 10:
            if (func_800088E4() != 1) {
                func_80017548();
            }
            ProcPostEvent(31);
            ProcPostMessage(task, 31, 0);
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
