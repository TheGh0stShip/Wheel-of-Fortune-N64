// InitGraphics.c -- loads segment 1 from the cartridge and gives each gfxInfo its framebuffer

#include "wof.h"

/*
=====================
InitGraphics

Loads segment 1 from the cartridge and gives each gfxInfo its framebuffer.
=====================
*/
void InitGraphics(void) {
    s32 size;

    size = staticSize;
    camX = camY = camZ = camRoll = camPitch = camHeading = 0.0f;
    staticSegment = AllocMem(size);
    ReadRom(staticRom, staticSegment, size);
    gfxInfo[0].msg.type = OS_SC_DONE_MSG;
    gfxInfo[0].framebuffer = D_803B5000;
    gfxInfo[1].msg.type = OS_SC_DONE_MSG;
    gfxInfo[1].framebuffer = D_803DA800;
    osViSetSpecialFeatures(64);
}
