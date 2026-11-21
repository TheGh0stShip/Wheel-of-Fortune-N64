// DrawBonusTimer.c -- the draw function of bonusTimerImages

#include "wof.h"

/*
=====================
DrawBonusTimer

The draw function of bonusTimerImages.
=====================
*/
void DrawBonusTimer(obj_t *obj, frame_t *frame) {
    s32 unused[2];  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */
    s32 i;
    s32 unused2;  /* NOTE: unused in the original */

    gDPPipeSync(glistp++);
    gSPDisplayList(glistp++, &D_01021970);
    gDPSetCycleType(glistp++, G_CYC_COPY);
    for (i = 0; i < 2; i++) {
        DrawImage(&bonusTimerImages[i], 1);
    }
}
