// wof_graphics.c -- the colours of the scene's lights and the start of the graphics: segment 1 and
// the framebuffers
//
// SetLightColor ends off an 8-byte boundary with InitGraphics right after, which happens only inside an
// object. Whether LoadSceneData, createGfxTask and ResetScissor after it are this object's too, and
// where it starts after ReadControllers, the text does not say.

#include "wof.h"

// guess: the RCS run at 0x800004F0 opens this object's read-only data. The #ident line of the system
// header the object included put the string there, and zeros to an 8-byte boundary follow it before
// SetLightColor's jump table, which needs that boundary itself. The run may instead be all the
// read-only data of an object between ReadControllers and SetLightColor (the rumble's, say), whose
// text uses none; the bytes are the same either way. This reading needs one object start fewer (no
// object whose read-only data opens without a run at 0x80000508), and it is how the runs at 0x80000B00
// and 0x80000E28, also followed by zeros and the next functions' data, are read.
#ident "$Revision: 1.17 $"

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
