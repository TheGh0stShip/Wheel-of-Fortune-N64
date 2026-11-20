#include "wof.h"


struct procResult_s func_8001BED8(proc_t *proc) {
    struct procResult_s sp10;
    proc_t *task;
    s32 unused;  /* NOTE: unused in the original */
    s32 event;
    f32 ratio;

    sp10.w[1] = 1;
    sp10.w[0] = 0;
    if (proc->data->playerProc.player != D_800FB808) {
        ProcClearMessages(proc);
        return sp10;
    }
    task = FindProc(0x5000000, -1);
    while ((event = ProcGetMessage(proc)) != 0) {
        switch (event) {
        case 8:
            func_80017C00(3, 1);
            switch (func_800082E4()) {
            case 4:
                if (Random(100) >= 11) {
                    func_8002EB90(func_8001A894(proc->data->playerProc.unk_0C, proc) & 255);
                } else {
                    func_8002EB90(func_8001A97C(proc->data->playerProc.unk_0C) & 255);
                }
                break;
            case 2:
                func_8002EB90(func_8001A97C(proc->data->playerProc.unk_0C) & 255);
                break;
            case 3:
                func_8002EB90(func_8001A894(proc->data->playerProc.unk_0C, proc) & 255);
                break;
            }
            ProcPostMessage(proc, 5, 0);
            sp10.w[1] = 1;
            sp10.w[0] = 60 / frameRetraces;
            return sp10;
            break;
        case 5:
            PlaySound(D_800B9990[D_800FB808].unk_0FC + (D_800B61B5 - 65));
            ProcPostMessage(proc, 44, 0);
            sp10.w[1] = 1;
            sp10.w[0] = 30 / frameRetraces;
            return sp10;
        case 44:
            task = FindProc(0x5010000, -1);
            ProcPostMessage(task, 23, 0);
            if (func_80007888(D_800B61B5, 2) > 0) {
                func_80007DAC(D_800B61B5);
                task = CreatProc(func_80010574, 0x1000000);
                task->data->data80010574.letter = D_800B61B5;
                sp10.w[1] = 2;
                sp10.w[0] = 6;
                return sp10;
            } else {
                PlaySound(1);
                func_80017548();
                ProcPostEvent(24);
                ProcPostEvent(31);
                ProcPostMessage(task, 31, 0);
                sp10.w[1] = 0;
                sp10.w[0] = 0;
                return sp10;
            }
        case 6:
            func_80029974(0);
            func_8002FD50();
            ratio = CheckPercentDone();
            if (ratio > 0.7) {
                task = CreatProc(func_8001BC44, proc->data->playerProc.player | 0x2000300);
                task->data->playerProc.player = proc->data->playerProc.player;
                task->data->playerProc.unk_0C = proc->data->playerProc.unk_0C;
                sp10.w[1] = 2;
                sp10.w[0] = 10;
                return sp10;
            } else {
                sp10.w[1] = 1;
                sp10.w[0] = 0;
                return sp10;
            }
        case 33:
            PlaySound(1);
        case 10:
            if (func_800088E4() != 1) {
                func_80017548();
            }
            ProcPostEvent(24);
            ProcPostEvent(31);
            ProcPostMessage(task, 31, 0);
            sp10.w[1] = 0;
            sp10.w[0] = 0;
            return sp10;
        case 34:
            sp10.w[1] = 0;
            sp10.w[0] = 0;
            return sp10;
        }
    }
    return sp10;
}
