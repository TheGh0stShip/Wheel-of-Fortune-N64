// DrawNoController.c -- the draw function of the screen shown when no controller is in

#include "wof.h"

/*
=====================
DrawNoController

The draw function of the screen shown when no controller is in.
=====================
*/
void DrawNoController(obj_t *obj, frame_t *frame) {
    s32 i;

    gDPPipeSync(glistp++);
    gSPDisplayList(glistp++, D_01021970);
    gDPSetCycleType(glistp++, G_CYC_COPY);
    for (i = 0; i < 2; i++) {
        DrawImage(&noControllerImages[i], 1);
    }
}
