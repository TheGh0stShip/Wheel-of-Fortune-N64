// SetGameView.c -- setView for a step of a turn

#include "wof.h"

/*
=====================
SetGameView

SetView for a step of a turn.
=====================
*/
void SetGameView(s32 view, s32 cpu) {
    obj_t *obj;
    proc_t *task;

    obj = FindObj(0x3000000, 0xFF000000);
    task = FindProc(0x2010000, 0xFFFF0000);
    if (task != 0) {
        KillProc(task, 1);
    }
    switch (view) {
    case 0:
        SetView(obj, playerViews[curPlayer]);
        return;
    case 1:
        task = FindProc(0x2010000, 0xFFFF0000);
        if (task == 0 && cpu == 0) {
            task = CreatProc(AdjustCameraProc, curPlayer | 0x2010000);
            task->data->adjustCamera.player = curPlayer;
        }
        SetView(obj, view);
        return;
    case 3:
        if (round == 2) {
            SetView(obj, 18);
        } else {
            SetView(obj, view);
        }
        return;
    }
    SetView(obj, view);
}
