#include "wof.h"
#include "rumble.h"


struct procResult_s func_800183A8(proc_t *proc) {
    struct procResult_s result;
    proc_t *task;
    obj_t *node;
    s32 event;

    result.w[1] = 1;
    result.w[0] = 0;
    if (proc->data->playerProc.player != D_800FB808) {
        ProcClearMessages(proc);
        return result;
    }
    while ((event = ProcGetMessage(proc)) != 0) {
        switch (event) {
        case 8:
            func_80017C00(0, 0);
            task = CreatProc(func_8000EF68, 0x4000000);
            result.w[1] = 2;
            result.w[0] = 29;
            return result;
        case 29:
            func_80017C00(0, 0);
            task = CreatProc(func_8000FDFC, 0x4030000);
            node = FindObj(0x4010000, 0xFFFF0000);
            task->data->data8000FDFC.unk_00 = node;
            if (D_800BCCF0 > 50.0f) {
                task->data->data8000FDFC.unk_0C = D_800BCCF0 + guRandom() % 10;
            } else {
                task->data->data8000FDFC.unk_0C = (f32)(guRandom() % 10 + 50) + D_800BCCF0;
            }
            if (task->data->data8000FDFC.unk_0C > 80.0) {
                ProcPostMessage(proc, 7, 0);
                result.w[1] = 1;
                result.w[0] = 40 / frameRetraces;
                return result;
            } else {
                result.w[1] = 2;
                result.w[0] = -1;
                return result;
            }
            break;
        case 7:
            task = FindProc(0x4030000, -1);
            if (task->data->data8000FDFC.unk_0C >= 110.0) {
                if (guRandom() % 100 >= 51) {
                    func_80017C00(11, 0);
                } else {
                    func_80017C00(15, 1);
                }
            } else {
                func_80017C00(3, 0);
            }
            result.w[1] = 2;
            result.w[0] = 4;
            break;
        case 4:
            func_80017C00(0, 0);
            result.w[1] = 2;
            result.w[0] = 2;
            break;
        case 2:
            node = FindObj(0x4010000, 0xFFFF0000);
            func_80009364(0);
            if (func_8000928C() == -2 || func_8000928C() == -1) {
                func_80017C00(0, 0);
                func_80032B80();
                StartRumble(D_800B9990[D_800FB808].unk_014, 30, 0.8f);
                if (func_80017728() != 0) {
                    if (func_8000928C() == -2) {
                        func_80021B04(12, 16);
                        result.w[1] = 2;
                        result.w[0] = 16;
                        return result;
                    } else {
                        if (func_80033150(1, 16, D_800FB808) != 0) {
                            result.w[1] = 2;
                            result.w[0] = 16;
                        } else {
                            func_80017548();
                            ProcPostEvent(3);
                            result.w[1] = 0;
                        }
                        return result;
                    }
                }
                func_80017548();
                result.w[1] = 0;
                result.w[0] = 0;
                return result;
            }
            func_80017C00(3, 0);
            func_80032B10();
            func_8002EB40();
            result.w[1] = 2;
            result.w[0] = 5;
            break;
        case 16:
            func_80017548();
            ProcPostEvent(3);
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
            if (func_80007888(D_800B61B5, 0) > 0) {
                func_80007DAC(D_800B61B5);
                task = CreatProc(func_80010574, 0x1000000);
                task->data->data80010574.letter = D_800B61B5;
                result.w[1] = 2;
                result.w[0] = 6;
            } else {
                PlaySound(1);
                StartRumble(D_800B9990[D_800FB808].unk_014, 30, 0.8f);
                if (func_80017548() != 0) {
                    ProcPostEvent(3);
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
