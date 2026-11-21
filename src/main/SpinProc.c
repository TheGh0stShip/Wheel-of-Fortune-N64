#include "wof.h"
#include "rumble.h"


struct procResult_s SpinProc(proc_t *proc) {
    struct procResult_s result;
    proc_t *task;
    obj_t *node;
    s32 event;

    result.w[1] = 1;
    result.w[0] = 0;
    if (proc->data->playerProc.player != curPlayer) {
        ProcClearMessages(proc);
        return result;
    }
    while ((event = ProcGetMessage(proc)) != 0) {
        switch (event) {
        case 8:
            SetGameView(0, 0);
            task = CreatProc(WheelPullProc, 0x4000000);
            result.w[1] = 2;
            result.w[0] = 29;
            return result;
        case 29:
            SetGameView(0, 0);
            task = CreatProc(WheelSpinProc, 0x4030000);
            node = FindObj(0x4010000, 0xFFFF0000);
            task->data->wheelSpin.wheel = node;
            if (wheelSpeed > 50.0f) {
                task->data->wheelSpin.speed = wheelSpeed + guRandom() % 10;
            } else {
                task->data->wheelSpin.speed = (f32)(guRandom() % 10 + 50) + wheelSpeed;
            }
            if (task->data->wheelSpin.speed > 80.0) {
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
            if (task->data->wheelSpin.speed >= 110.0) {
                if (guRandom() % 100 >= 51) {
                    SetGameView(11, 0);
                } else {
                    SetGameView(15, 1);
                }
            } else {
                SetGameView(3, 0);
            }
            result.w[1] = 2;
            result.w[0] = 4;
            break;
        case 4:
            SetGameView(0, 0);
            result.w[1] = 2;
            result.w[0] = 2;
            break;
        case 2:
            node = FindObj(0x4010000, 0xFFFF0000);
            ApplyWedge(0);
            if (GetWedgeValue() == -2 || GetWedgeValue() == -1) {
                SetGameView(0, 0);
                func_80032B80();
                StartRumble(players[curPlayer].controller, 30, 0.8f);
                if (func_80017728() != 0) {
                    if (GetWedgeValue() == -2) {
                        func_80021B04(12, 16);
                        result.w[1] = 2;
                        result.w[0] = 16;
                        return result;
                    } else {
                        if (func_80033150(1, 16, curPlayer) != 0) {
                            result.w[1] = 2;
                            result.w[0] = 16;
                        } else {
                            LoseTurn();
                            ProcPostEvent(3);
                            result.w[1] = 0;
                        }
                        return result;
                    }
                }
                LoseTurn();
                result.w[1] = 0;
                result.w[0] = 0;
                return result;
            }
            SetGameView(3, 0);
            func_80032B10();
            StartLetterPick();
            result.w[1] = 2;
            result.w[0] = 5;
            break;
        case 16:
            LoseTurn();
            ProcPostEvent(3);
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        case 5:
            PlaySound(players[curPlayer].letterSounds + (curLetter - 65));
            ProcPostMessage(proc, 44, 0);
            result.w[1] = 1;
            result.w[0] = 30 / frameRetraces;
            return result;
        case 44:
            func_8002A014();
            if (CallLetter(curLetter, 0) > 0) {
                ShowLetter(curLetter);
                task = CreatProc(LightLetterProc, 0x1000000);
                task->data->lightLetter.letter = curLetter;
                result.w[1] = 2;
                result.w[0] = 6;
            } else {
                PlaySound(1);
                StartRumble(players[curPlayer].controller, 30, 0.8f);
                if (LoseTurn() != 0) {
                    ProcPostEvent(3);
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
