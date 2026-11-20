#include "wof.h"


struct procResult_s CpuSpinProc(proc_t *proc) {
    struct procResult_s result;
    proc_t *task;
    obj_t *target;
    s32 event;

    result.w[1] = 1;
    result.w[0] = 0;
    if (proc->data->playerProc.player != curPlayer) {
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
            SetGameView(0, 1);
            task = CreatProc(WheelSpinProc, 0x4000000);
            target = FindObj(0x4010000, 0xFFFF0000);
            task->data->data8000FDFC.unk_00 = target;
            task->data->data8000FDFC.unk_0C = (f32)(guRandom() % 50 + 100);
            if ((f64)task->data->data8000FDFC.unk_0C > 80.0) {
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
                SetGameView(15, 1);
            } else {
                SetGameView(3, 1);
            }
            result.w[1] = 2;
            result.w[0] = 4;
            return result;
            break;
        case 4:
            SetGameView(0, 1);
            result.w[1] = 2;
            result.w[0] = 2;
            return result;
            break;
        case 2:
            target = FindObj(0x4010000, 0xFFFF0000);
            ApplyWedge(0);
            if (GetWedgeValue() == -1) {
                func_80032B80();
                SetGameView(0, 1);
                if (LoseTurn() != 0) {
                    ProcPostEvent(3);
                    ProcPostEvent(24);
                }
                result.w[1] = 0;
                result.w[0] = 0;
                return result;
            } else {
                if (GetWedgeValue() == -2) {
                    func_80032B80();
                    SetGameView(0, 1);
                    if (func_80017728() != 0) {
                        func_80021B04(12, 16);
                        result.w[1] = 2;
                        result.w[0] = 16;
                        return result;
                    }
                    LoseTurn();
                    result.w[1] = 0;
                    result.w[0] = 0;
                    return result;
                }
            }
            func_80032B10();
            SetGameView(3, 1);
            StartCpuLetterPick(CpuPickConsonant(proc->data->playerProc.unk_0C, proc) & 255);
            ProcPostMessage(proc, 5, 0);
            result.w[1] = 1;
            result.w[0] = 60 / frameRetraces;
            return result;
        case 16:
            LoseTurn();
            ProcPostEvent(3);
            ProcPostEvent(24);
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        case 5:
            PlaySound(players[curPlayer].unk_0FC + (curLetter - 65));
            ProcPostMessage(proc, 44, 0);
            result.w[1] = 1;
            result.w[0] = 30 / frameRetraces;
            return result;
        case 44:
            func_8002A014();
            task = FindProc(0x5010000, -1);
            ProcPostMessage(task, 23, 0);
            if (CallLetter(curLetter, 0) > 0) {
                ShowLetter(curLetter);
                task = CreatProc(LightLetterProc, 0x1000000);
                task->data->data80010574.letter = curLetter;
                result.w[1] = 2;
                result.w[0] = 6;
                return result;
            } else {
                PlaySound(1);
                if (LoseTurn() != 0) {
                    ProcPostEvent(3);
                    ProcPostEvent(24);
                }
                result.w[1] = 0;
                result.w[0] = 0;
                return result;
            }
            break;
        case 6:
            if (GetWedgeValue() == -3) {
                jackpotWon = 1;
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
