// PauseGame.c -- pauses: gameMode 6, the sounds paused, the pause picture shown

#include "wof.h"

// guess: the RCS run at 0x80001A30 opens this object's read-only data, and is all of it. The run
// is the #ident line of the system header the object included; zeros to an 8-byte boundary and the
// next run follow it, and no function uses it. It lies between wof_anim's read-only data and the
// runs at 0x80001A48 and 0x80001A60, so it opens an object that starts after one of
// HideOtherContestants, PauseGame and PauseProc. Of those, this reading takes the first: the pause's
// three functions as one object, the run at 0x80001A48 opening the object at the 4-byte gap after
// StartPauseProc (wof_applause) and the one at 0x80001A60 the confetti's. The bytes are the same for
// each choice.
#ident "$Revision: 1.17 $"

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
