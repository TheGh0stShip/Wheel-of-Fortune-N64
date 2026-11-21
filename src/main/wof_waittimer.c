// wof_waittimer.c -- starting and stopping the proc of func_8002FB60, which posts event 48 after five
// seconds
//
// func_8002FCD8 ends off an 8-byte boundary with func_8002FD14 right after, which happens only inside
// an object. Whether func_8002FB60 before it and StartSolveTimer after it are this object's the text
// does not say.

#include "wof.h"

void func_8002FCD8(void) {
    CreatProc(func_8002FB60, 0x07050000);
}

void func_8002FD14(void) {
    KillProcClass(0x07050000, -1, 0);
}
