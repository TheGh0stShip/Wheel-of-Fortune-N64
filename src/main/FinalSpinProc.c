// FinalSpinProc.c -- the host's final spin when the time runs out: "Final spin is "

#include "wof.h"


/*
=====================
FinalSpinProc

The host's final spin when the time runs out: "Final spin is ".
=====================
*/
struct procResult_s FinalSpinProc(proc_t *proc) {
    struct procResult_s result;
    proc_t *task;
    obj_t *node;
    s32 event;

    result.w[1] = 1;
    result.w[0] = 0;
    while ((event = ProcGetMessage(proc)) != 0) {
        switch (event) {
        case 8:
            ProcPostMessage(proc, 41, 0);
            result.w[1] = 1;
            result.w[0] = 180 / frameRetraces;
            return result;
        case 41:
            PlayMovieCorner(8, 44);
            result.w[1] = 2;
            result.w[0] = 44;
            return result;
        case 2:
            ApplyWedge(1);
            if (GetWedgeValue() <= 0 || GetWedgeValue() == 10000) {
                result.w[1] = 1;
                result.w[0] = 60 / frameRetraces;
                return result;
            }
            ProcPostEvent(32);
            PrintStr("Final spin is ");
            PrintNum(GetWedgeValue());
            PrintStr("\n");
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        }
    }
    SetGameView(0, 1);
    task = CreatProc(WheelSpinProc, 0x4000000);
    node = FindObj(0x4010000, 0xFFFF0000);
    task->data->wheelSpin.wheel = node;
    task->data->wheelSpin.speed = guRandom() % 25 + 75;
    result.w[1] = 2;
    result.w[0] = 2;
    return result;
}
