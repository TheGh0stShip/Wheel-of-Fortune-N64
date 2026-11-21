// StartApplause.c -- creates ApplauseProc

#include "wof.h"

/*
=====================
StartApplause

Creates ApplauseProc.
=====================
*/
void StartApplause(void) {
    CreatProc(ApplauseProc, 0x0C000000);
}
