#include "wof.h"

extern Gfx *D_800B81E8;

void func_800223A4(s32 arg0, s32 arg1) {
    s32 pad0[2];
    s32 i;
    s32 pad1;
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
    for (i = 0; i < 118; i++) {
        func_800278A8((s32)&D_80059120[i], 1);
    }
    i = 0;
    while (i < 7) {
        func_800278A8((s32)&D_80058EB0[i], 1);
        i++;
    }
}
