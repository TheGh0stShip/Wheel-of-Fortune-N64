#include "wof.h"


void func_800278F0(obj_t *obj, frame_t *frame) {
    s32 unused[2];  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */
    s32 i;
    s32 j;

    gDPPipeSync(glistp++);
    gSPDisplayList(glistp++, &D_01021970);
    gDPSetCycleType(glistp++, G_CYC_COPY);
    i = 2;
    while (i >= 0) {
        j = 0;
        while (j < 2) {
            func_800278A8(&D_8005A4B8[i][j], 1);
            j++;
        }
        i--;
    }
    i = 0;
    while (i < 3) {
        j = 0;
        while (j < 7) {
            func_800278A8(&D_8005ADD0[i][j], 1);
            j++;
        }
        i++;
    }
    if (round == 2 && (D_800B40C4 != 0 || D_800BCA28 == 22)) {
        switch (curView) {
        case 3:
        case 18:
            j = 0;
            while (j < 3) {
                func_800278A8(&D_8005B630[j], 1);
                j++;
            }
            j = 0;
            while (j < 9) {
                func_800278A8(&D_8005B4C8[j], 1);
                func_800278A8(&D_8005B360[j], 1);
                j++;
            }
        }
    }
    i = 0;
    while (i < 26) {
        if (uncalled[i] == ' ') {
            D_8005A998[i].unk_20 = D_8005A8C8[i];
        } else {
            D_8005A998[i].unk_20 = D_8005A930[i];
        }
        func_800278A8(&D_8005A998[i], 1);
        i++;
    }
    i = 0;
    while (i < 4) {
        func_800278A8(&D_8005A828[i], 1);
        i++;
    }
    i = 0;
    while (i < 3) {
        if (players[i].freeSpin != 0) {
            func_800278A8(&D_8005A7B0[i], 1);
        }
        if (players[i].hasPrize != 0) {
            func_800278A8(&D_8005A5A8[i], 1);
        }
        i++;
    }
    i = 0;
    while (i < 22) {
        func_800278A8(&D_8005B710[i], 1);
        i++;
    }
}
