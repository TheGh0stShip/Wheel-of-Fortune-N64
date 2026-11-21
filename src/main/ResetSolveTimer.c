// ResetSolveTimer.c -- starts the solve timer over, in the final spin

#include "wof.h"


/*
=====================
ResetSolveTimer

Starts the solve timer over, in the final spin.
=====================
*/
void ResetSolveTimer(void) {
    proc_t *task;

    if (finalSpin == 0 || gameMode == 4) {
        return;
    }
    task = FindProc(0x7030000, -1);
    if (task == 0) {
        FatalError("ResetSolveTimer: Solve Timer Proc does not exist.\n");
    }
    ProcPostMessage(task, 8, 0);
}
