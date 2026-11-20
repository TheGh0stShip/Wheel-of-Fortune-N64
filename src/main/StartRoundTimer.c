#include "wof.h"

void StartRoundTimer(void) {
    gameOver = 0;
    CreatProc(RoundTimerProc, 0x07010000);
}
