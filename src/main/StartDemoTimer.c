#include "wof.h"

void StartDemoTimer(void) {
    CreatProc(DemoTimerProc, 0x07040000);
}
