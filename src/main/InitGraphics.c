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

    size = D_8006DCF0;
    D_800BEE2C = D_800BEE30 = D_800BEE34 = D_800BEE3C = D_800BEE40 = D_800BEE44 = 0.0f;
    staticSegment = func_8000B924(size);
    ReadRom(D_8006DCEC, staticSegment, size);
    gfxInfo[0].msg.type = OS_SC_DONE_MSG;
    gfxInfo[0].framebuffer = D_803B5000;
    gfxInfo[1].msg.type = OS_SC_DONE_MSG;
    gfxInfo[1].framebuffer = D_803DA800;
    osViSetSpecialFeatures(64);
}
