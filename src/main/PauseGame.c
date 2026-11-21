// PauseGame.c -- pauses: gameMode 6, the sounds paused, the pause picture shown

#include "wof.h"

/*
=====================
PauseGame

Pauses: gameMode 6, the sounds paused, the pause picture shown.
=====================
*/
void PauseGame(void) {
    if (movieDone == 0) {
        return;
    }
    ResetMotors();
    pauseStart = (s32)(osGetTime() / osClockRate);
    pausedMode = gameMode;
    gameMode = 6;
    MakeObj(0, 0, DrawPause, 0x5020000);
    PauseSounds();
}
