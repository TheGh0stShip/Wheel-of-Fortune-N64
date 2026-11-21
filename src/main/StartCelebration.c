// StartCelebration.c -- the movie and the confetti of a win

#include "wof.h"

/*
=====================
StartCelebration

The movie and the confetti of a win.
=====================
*/
void StartCelebration(void) {
    D_800B81E4 = &D_8006DDC4;
    PlayMovie(0x16, 0, 0x28, 0xF);
    CreatProc(ConfettiBurstProc, 0x05030000);
}
