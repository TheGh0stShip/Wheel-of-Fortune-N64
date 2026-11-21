#include "wof.h"


void DrawLetterPick(obj_t *obj, frame_t *frame) {
    s32 unused[2];  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */
    s32 i;
    s32 unused2;  /* NOTE: unused in the original */

    gDPPipeSync(glistp++);
    gSPDisplayList(glistp++, &D_01021970);
    gDPSetCycleType(glistp++, G_CYC_COPY);
    i = 0;
    while (i < 26) {
        if (uncalled[i] == ' ') {
            letterImages[i].unk_20 = D_8005A8C8[i];
        } else {
            letterImages[i].unk_20 = D_8005A930[i];
        }
        DrawImageAt(&letterImages[i], 1, -13, 0);
        i++;
    }
    i = 0;
    while (i < 22) {
        DrawImage(&categoryImages[i], 1);
        i++;
    }
    i = 0;
    while (i < 10) {
        DrawImage(&D_8005BE00[i], 1);
        i++;
    }
}
