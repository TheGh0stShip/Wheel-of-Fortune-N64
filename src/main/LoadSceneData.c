#include "wof.h"

/*
=====================
LoadSceneData

Waits for the graphics, saves the memory stack and reads a block from the cartridge; each screen
starts with it.
=====================
*/
void LoadSceneData(void) {
    s32 sp10;

    sp10 = D_8006DCF8;
    while (pendingGfx != 0 && retraceCount < 100) {
    }
    PushMemStack();
    D_800B9CF4 = func_8000B924(sp10);
    ReadRom(D_8006DCF4, D_800B9CF4, sp10);
}
