// StartRoundTimer.c -- creates RoundTimerProc

#include "wof.h"

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
