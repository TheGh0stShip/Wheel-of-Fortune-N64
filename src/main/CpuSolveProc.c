// CpuSolveProc.c -- the machine solves

#include "wof.h"

/*
=====================
CpuSolveProc

The machine solves.
=====================
*/
struct procResult_s CpuSolveProc(proc_t *proc) {
    struct procResult_s result;
    proc_t *task;
    s32 unused;  /* NOTE: unused in the original */
    s32 event;

    result.w[1] = 1;
    result.w[0] = 0;
    if (proc->data->playerProc.player != curPlayer) {
        ProcClearMessages(proc);
        return result;
    }
    task = FindProc(0x1020000, -1);
    while ((event = ProcGetMessage(proc)) != 0) {
        switch (event) {
        case 8:
            StartSolvePuzzle();
            SetGameView(3, 1);
            result.w[1] = 2;
            result.w[0] = 5;
            return result;
        case 5:
            if (CheckSolve() == 1) {
                ProcPostMessage(task, 19, 0);
                ProcPostEvent(24);
                ProcPostEvent(10);
                result.w[1] = 0;
                result.w[0] = 0;
            } else {
                ProcPostMessage(task, 20, 0);
                PlaySound(1);
                if (LoseTurn() != 0) {
                    ProcPostEvent(10);
                    ProcPostEvent(24);
                }
                result.w[1] = 0;
                result.w[0] = 0;
                return result;
            }
            break;
        case 34:
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        }
    }
    return result;
}
