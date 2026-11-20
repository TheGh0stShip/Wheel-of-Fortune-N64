#include "wof.h"

void func_80027F3C(s32 arg0, s32 arg1) {
    s32 unused[2];  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */
    s32 unused2;  /* NOTE: unused in the original */
    s32 i;

    gDPPipeSync(D_800B81E8++);
    gSPDisplayList(D_800B81E8++, &D_01021970);
    gDPSetCycleType(D_800B81E8++, G_CYC_COPY);
    for (i = 0; i < 9; i++) {
        func_800278A8((s32)&D_8005B4C8[i], 1);
    }
}
