#include "wof.h"

void func_8002842C(s32 arg0, s32 arg1) {
    s32 unused[2];  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */
    s32 i;
    s32 unused2;  /* NOTE: unused in the original */

    gDPPipeSync(D_800B81E8++);
    gSPDisplayList(D_800B81E8++, &D_01021970);
    gDPSetCycleType(D_800B81E8++, G_CYC_COPY);
    for (i = 0; i < 7; i++) {
        func_800278A8((s32)&D_8005B1A8[i], 1);
    }
}
