// wof_starttimers.c -- starting the solve timer and the round timer, and starting the solve timer over
//
// StartSolveTimer and ResetSolveTimer each end off an 8-byte boundary with the next function right
// after, which happens only inside an object. Whether func_8002FD14 before it and StartDemoTimer after
// it are this object's the text does not say.

#include "wof.h"

/*
=====================
StartSolveTimer

Creates SolveTimerProc.
=====================
*/
void StartSolveTimer(void) {
    CreatProc(SolveTimerProc, 0x07030000);
}

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

/*
=====================
StartRoundTimer

Creates RoundTimerProc.
=====================
*/
void StartRoundTimer(void) {
    gameOver = 0;
    CreatProc(RoundTimerProc, 0x07010000);
}
