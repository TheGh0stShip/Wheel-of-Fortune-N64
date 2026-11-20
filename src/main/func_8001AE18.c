#include "wof.h"


struct procResult_s func_8001AE18(proc_t *proc) {
    struct procResult_s result;
    proc_t *task;
    obj_t *target;
    s32 event;

    result.w[1] = 1;
    result.w[0] = 0;
    if (proc->unk_30->playerProc.player != D_800FB808) {
        ProcClearMessages(proc);
        return result;
    }
    for (;;) {
        event = ProcGetMessage(proc);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 8:
            func_80017C00(0, 1);
            task = CreatProc(func_8000FDFC, 0x4000000);
            target = FindObj(0x4010000, 0xFFFF0000);
            task->unk_30->data8000FDFC.unk_00 = target;
            task->unk_30->data8000FDFC.unk_0C = (f32)(guRandom() % 50 + 100);
            if ((f64)task->unk_30->data8000FDFC.unk_0C > 80.0) {
                ProcPostMessage(proc, 7, 0);
                result.w[1] = 1;
                result.w[0] = 30 / frameRetraces;
                return result;
            } else {
                result.w[1] = 2;
                result.w[0] = -1;
                return result;
            }
            break;
        case 7:
            if (Random(100) >= 76) {
                func_80017C00(15, 1);
            } else {
                func_80017C00(3, 1);
            }
            result.w[1] = 2;
            result.w[0] = 4;
            return result;
            break;
        case 4:
            func_80017C00(0, 1);
            result.w[1] = 2;
            result.w[0] = 2;
            return result;
            break;
        case 2:
            target = FindObj(0x4010000, 0xFFFF0000);
            func_80009364(0);
            if (func_8000928C() == -1) {
                func_80032B80();
                func_80017C00(0, 1);
                if (func_80017548() != 0) {
                    ProcPostEvent(3);
                    ProcPostEvent(24);
                }
                result.w[1] = 0;
                result.w[0] = 0;
                return result;
            } else {
                if (func_8000928C() == -2) {
                    func_80032B80();
                    func_80017C00(0, 1);
                    if (func_80017728() != 0) {
                        func_80021B04(12, 16);
                        result.w[1] = 2;
                        result.w[0] = 16;
                        return result;
                    }
                    func_80017548();
                    result.w[1] = 0;
                    result.w[0] = 0;
                    return result;
                }
            }
            func_80032B10();
            func_80017C00(3, 1);
            func_8002EB90(func_8001A894(proc->unk_30->playerProc.unk_0C, proc) & 255);
            ProcPostMessage(proc, 5, 0);
            result.w[1] = 1;
            result.w[0] = 60 / frameRetraces;
            return result;
        case 16:
            func_80017548();
            ProcPostEvent(3);
            ProcPostEvent(24);
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        case 5:
            PlaySound(D_800B9990[D_800FB808].unk_0FC + (D_800B61B5 - 65));
            ProcPostMessage(proc, 44, 0);
            result.w[1] = 1;
            result.w[0] = 30 / frameRetraces;
            return result;
        case 44:
            func_8002A014();
            task = FindProc(0x5010000, -1);
            ProcPostMessage(task, 23, 0);
            if (func_80007888(D_800B61B5, 0) > 0) {
                func_80007DAC(D_800B61B5);
                task = CreatProc(func_80010574, 0x1000000);
                task->unk_30->data80010574.letter = D_800B61B5;
                result.w[1] = 2;
                result.w[0] = 6;
                return result;
            } else {
                PlaySound(1);
                if (func_80017548() != 0) {
                    ProcPostEvent(3);
                    ProcPostEvent(24);
                }
                result.w[1] = 0;
                result.w[0] = 0;
                return result;
            }
            break;
        case 6:
            if (func_8000928C() == -3) {
                D_800B96A0 = 1;
            }
            ProcPostEvent(24);
            ProcPostEvent(3);
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        case 34:
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        }
    }
    return result;
}
