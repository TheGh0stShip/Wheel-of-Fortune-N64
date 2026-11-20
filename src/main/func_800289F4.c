#include "wof.h"

extern image_t D_8005A760[];
extern Gfx *D_800B81E8;

void func_800289F4(s32 arg0, s32 arg1) {
    s32 i;
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
    for (i = 0; i < 2; i++) {
        func_800278A8((s32)&D_8005A760[i], 1);
    }
}
