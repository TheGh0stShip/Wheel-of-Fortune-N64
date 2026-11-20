#include "wof.h"

void func_80022530(obj_t *obj, frame_t *frame) {
    s32 unused[2];  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */
    s32 i;
    s32 unused2;  /* NOTE: unused in the original */

    gDPPipeSync(D_800B81E8++);
    gSPDisplayList(D_800B81E8++, &D_01021970);
    gDPSetCycleType(D_800B81E8++, G_CYC_COPY);
    i = 0;
    for (;;) {
        if (i >= 118) {
            break;
        }
        func_800278A8((s32)&D_80059120[i], 1);
        i++;
    }
    i = 0;
    for (;;) {
        if (i >= 7) {
            return;
        }
        func_800278A8((s32)&D_80059008[i], 1);
        i++;
    }
}
