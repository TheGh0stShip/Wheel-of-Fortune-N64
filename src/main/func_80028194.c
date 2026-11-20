#include "wof.h"


void func_80028194(s32 arg0, s32 arg1) {
    s32 unused[2];  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */
    s32 i;
    s32 unused2;  /* NOTE: unused in the original */

    gDPPipeSync(D_800B81E8++);
    gSPDisplayList(D_800B81E8++, &D_01021970);
    gDPSetCycleType(D_800B81E8++, G_CYC_COPY);
    i = 0;
    while (i < 26) {
        if (D_800B966A[i] == ' ') {
            D_8005A998[i].unk_20 = D_8005A8C8[i];
        } else {
            D_8005A998[i].unk_20 = D_8005A930[i];
        }
        func_8002741C((s32)&D_8005A998[i], 1, -13, 0);
        i++;
    }
    i = 0;
    while (i < 22) {
        func_800278A8((s32)&D_8005B710[i], 1);
        i++;
    }
    i = 0;
    while (i < 10) {
        func_800278A8((s32)&D_8005BE00[i], 1);
        i++;
    }
}
