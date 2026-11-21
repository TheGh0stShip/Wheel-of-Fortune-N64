#include "wof.h"

/*
=====================
StartDemoTimer

Creates DemoTimerProc.
=====================
*/
void StartDemoTimer(void) {
    CreatProc(DemoTimerProc, 0x07040000);
}
