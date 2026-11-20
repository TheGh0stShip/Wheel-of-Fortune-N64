#include "wof.h"

extern Gfx *D_800B81E8;
extern u8 D_800B966A[];

void func_800278F0(s32 arg0, s32 arg1) {
    s32 pad0[2];
    s32 i;
    s32 j;
    Gfx *gfx;

    gfx = D_800B81E8++;
    gfx->words.w0 = 0xE7000000;
    gfx->words.w1 = 0;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0x6000000;
    gfx->words.w1 = (s32)&D_01021970;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xBA001402;
    gfx->words.w1 = 0x200000;
    i = 2;
    while (i >= 0) {
        j = 0;
        while (j < 2) {
            func_800278A8((s32)&D_8005A4B8[i][j], 1);
            j++;
        }
        i--;
    }
    i = 0;
    while (i < 3) {
        j = 0;
        while (j < 7) {
            func_800278A8((s32)&D_8005ADD0[i][j], 1);
            j++;
        }
        i++;
    }
    if (D_800B619C == 2 && (D_800B40C4 != 0 || D_800BCA28 == 22)) {
        switch (D_800BA2BC) {
        case 3:
        case 18:
            j = 0;
            while (j < 3) {
                func_800278A8((s32)&D_8005B630[j], 1);
                j++;
            }
            j = 0;
            while (j < 9) {
                func_800278A8((s32)&D_8005B4C8[j], 1);
                func_800278A8((s32)&D_8005B360[j], 1);
                j++;
            }
        }
    }
    i = 0;
    while (i < 26) {
        if (D_800B966A[i] == ' ') {
            D_8005A998[i].unk_20 = D_8005A8C8[i];
        } else {
            D_8005A998[i].unk_20 = D_8005A930[i];
        }
        func_800278A8((s32)&D_8005A998[i], 1);
        i++;
    }
    i = 0;
    while (i < 4) {
        func_800278A8((s32)&D_8005A828[i], 1);
        i++;
    }
    i = 0;
    while (i < 3) {
        if (D_800B9990[i].unk_008 != 0) {
            func_800278A8((s32)&D_8005A7B0[i], 1);
        }
        if (D_800B9990[i].unk_00C != 0) {
            func_800278A8((s32)&D_8005A5A8[i], 1);
        }
        i++;
    }
    i = 0;
    while (i < 22) {
        func_800278A8((s32)&D_8005B710[i], 1);
        i++;
    }
}
