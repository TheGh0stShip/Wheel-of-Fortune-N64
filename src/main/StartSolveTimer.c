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
