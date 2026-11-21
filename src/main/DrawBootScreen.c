// DrawBootScreen.c -- the draw function of the first screen when a controller is in

#include "wof.h"

/*
=====================
DrawBootScreen

The draw function of the first screen when a controller is in.
=====================
*/
void DrawBootScreen(obj_t *obj, frame_t *frame) {
    s32 i;

    gDPPipeSync(glistp++);
    gSPDisplayList(glistp++, D_01021970);
    gDPSetCycleType(glistp++, G_CYC_COPY);
    for (i = 0; i < 8; i++) {
        DrawImage(&bootScreenImages[i], 1);
    }
}
