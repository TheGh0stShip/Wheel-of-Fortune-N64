#include "wof.h"

void func_8002208C(obj_t *obj, frame_t *frame) {
    s32 unused[2];  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */
    s32 i;
    s32 unused2;  /* NOTE: unused in the original */

    gDPPipeSync(D_800B81E8++);
    gSPDisplayList(D_800B81E8++, &D_01021970);
    gDPSetCycleType(D_800B81E8++, G_CYC_COPY);
    for (i = 0; i < 118; i++) {
        func_800278A8(&D_80059120[i], 1);
    }
    i = 0;
    while (i < 11) {
        func_800278A8(&D_800588F0[i], 1);
        i++;
    }
}
