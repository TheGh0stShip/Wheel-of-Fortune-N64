#include "wof.h"

void func_80028064(obj_t *obj, frame_t *frame) {
    s32 unused[2];  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */
    s32 i;
    s32 unused2;  /* NOTE: unused in the original */

    gDPPipeSync(glistp++);
    gSPDisplayList(glistp++, &D_01021970);
    gDPSetCycleType(glistp++, G_CYC_COPY);
    for (i = 0; i < 22; i++) {
        DrawImageAt(&categoryImages[i], 1, 10, 20);
    }
}
