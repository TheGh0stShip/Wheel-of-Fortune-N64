// StartPauseProc.c -- creates PauseProc

#include "wof.h"

/*
=====================
StartPauseProc

Creates PauseProc.
=====================
*/
void StartPauseProc(void) {
    CreatProc(PauseProc, 0x0B000000);
}
