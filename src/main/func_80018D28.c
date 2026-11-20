#include "wof.h"
#include "rumble.h"

struct procResult_s func_80018D28(proc_t *proc) {
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
    for (;;) {
        event = ProcGetMessage(proc);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 8:
            if (D_800B9990[D_800FB808].unk_000 < 250) {
                ProcPostMessage(proc, 51, 0);
                PlaySound(1);
                StartRumble(D_800B9990[D_800FB808].unk_014, 30, 0.8f);
                ret.w[1] = 1;
                ret.w[0] = 30 / frameRetraces;
                return ret;
            } else {
                if (func_800084E8() == 3) {
                    func_80021B04(1, 16);
                    ret.w[1] = 2;
                    ret.w[0] = 16;
                    return ret;
                } else {
                    func_80017C00(3, 0);
                    func_8002EB40();
                    ret.w[1] = 2;
                    ret.w[0] = 5;
                }
            }
            break;
        case 16:
            ProcPostEvent(9);
            ret.w[1] = 0;
            ret.w[1] = 0;
            return ret;
        case 5:
            PlaySound(D_800B9990[D_800FB808].unk_0FC + (D_800B61B5 - 'A'));
            ProcPostMessage(proc, 44, 0);
            ret.w[1] = 1;
            ret.w[0] = 30 / frameRetraces;
            return ret;
        case 44:
            if (func_80007888(D_800B61B5, 1) > 0) {
                func_80007DAC(D_800B61B5);
                task = CreatProc(func_80010574, 0x1000000);
                task->data->data80010574.letter = D_800B61B5;
                ret.w[1] = 2;
                ret.w[0] = 6;
            } else {
                PlaySound(1);
                StartRumble(D_800B9990[D_800FB808].unk_014, 30, 0.8f);
                if (func_80017548() != 0) {
                    ProcPostEvent(9);
                }
                ret.w[1] = 0;
                ret.w[0] = 0;
                return ret;
            }
            break;
        case 51:
            ProcPostMessage(proc, 52, 0);
            PlaySound(150);
            ret.w[1] = 1;
            ret.w[0] = 60 / frameRetraces;
            return ret;
        case 52:
            ProcPostEvent(9);
            func_80017548();
            ret.w[1] = 0;
            ret.w[0] = 0;
            return ret;
        case 6:
            ProcPostEvent(9);
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
