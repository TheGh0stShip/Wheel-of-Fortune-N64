// SolveProc.c -- a person solves the puzzle

#include "wof.h"
#include "rumble.h"


/*
=====================
SolveProc

A person solves the puzzle.
=====================
*/
struct procResult_s SolveProc(proc_t *proc) {
    struct procResult_s ret;
    proc_t *task;
    s32 unused;  /* NOTE: unused in the original */
    s32 event;

    ret.w[1] = 1;
    ret.w[0] = 0;
    if (proc->data->playerProc.player != curPlayer) {
        ProcClearMessages(proc);
        return ret;
    }
    task = FindProc(0x1020000, -1);
    while ((event = ProcGetMessage(proc)) != 0) {
        switch (event) {
        case 8:
            StartSolvePuzzle();
            SetGameView(3, 0);
            ret.w[1] = 2;
            ret.w[0] = 5;
            return ret;
        case 5:
            if (CheckSolve() == 1) {
                applause = applause + 2;
                ProcPostMessage(task, 19, 0);
                ProcPostEvent(10);
                ret.w[1] = 0;
                ret.w[0] = 0;
            } else {
                ProcPostMessage(task, 20, 0);
                PlaySound(1);
                StartRumble(players[curPlayer].controller, 30, 0.8f);
                if (finalSpin == 0) {
                    if (LoseTurn() != 0) {
                        ProcPostEvent(10);
                    }
                } else {
                    ProcPostEvent(10);
                }
                ret.w[1] = 0;
                ret.w[0] = 0;
                return ret;
            }
            break;
        case 34:
            ret.w[1] = 0;
            ret.w[0] = 0;
            return ret;
        }
    }
    return ret;
}
