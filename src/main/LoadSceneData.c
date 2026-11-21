// LoadSceneData.c -- waits for the graphics, saves the memory stack and reads a block from the
// cartridge; each screen starts with it

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

    sp10 = sceneDataSize;
    while (pendingGfx != 0 && retraceCount < 100) {
    }
    PushMemStack();
    sceneData = func_8000B924(sp10);
    ReadRom(sceneDataRom, sceneData, sp10);
}
