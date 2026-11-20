#include "wof.h"

void StartSolveTimer(void) {
    CreatProc(SolveTimerProc, 0x07030000);
}
