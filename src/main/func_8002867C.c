#include "wof.h"

void func_8002867C(s32 arg0, s32 arg1) {
    s32 unused[2];  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */
    s32 i;
    s32 unused2;  /* NOTE: unused in the original */

    gDPPipeSync(glistp++);
    gSPDisplayList(glistp++, &D_01021970);
    gDPSetCycleType(glistp++, G_CYC_COPY);
    for (i = 0; i < 2; i++) {
        DrawImage(&D_8005B310[i], 1);
    }
}
