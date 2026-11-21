// wof_graphics.c -- the colours of the scene's lights and the start of the graphics: segment 1 and
// the framebuffers
//
// SetLightColor ends off an 8-byte boundary with InitGraphics right after, which happens only inside an
// object. Whether LoadSceneData, createGfxTask and ResetScissor after it are this object's too, and
// where it starts after ReadControllers, the text does not say.

#include "wof.h"

/*
=====================
SetLightColor

GSPLightColor on one of the six lights.
=====================
*/
void SetLightColor(s32 light) {
    switch (light) {
    case 1:
        gSPLightColor(glistp++, LIGHT_1, 0x505050FF);
        return;
    case 2:
        gSPLightColor(glistp++, LIGHT_2, 0x8C8C8CFF);
        return;
    case 3:
        gSPLightColor(glistp++, LIGHT_3, 0x8C8C8CFF);
        return;
    case 4:
        gSPLightColor(glistp++, LIGHT_4, 0x8C8C8CFF);
        return;
    case 5:
        gSPLightColor(glistp++, LIGHT_5, 0x8C8C8CFF);
        return;
    case 6:
        gSPLightColor(glistp++, LIGHT_6, 0x141414FF);
        return;
    }
}

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
