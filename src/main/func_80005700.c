#include "wof.h"

void func_80005700(void) {
    s32 sp10;

    sp10 = D_8006DCF8;
    while (pendingGfx != 0 && retraceCount < 100) {
    }
    PushMemStack();
    D_800B9CF4 = func_8000B924(sp10);
    ReadRom(D_8006DCF4, D_800B9CF4, sp10);
}
