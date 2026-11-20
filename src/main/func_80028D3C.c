#include "wof.h"

extern Gfx *D_800B81E8;

void func_80028D3C(s32 arg0, s32 arg1) {
    s32 pad0[4];
    Gfx *gfx;
    Gfx *gfx2;

    gfx = D_800B81E8++;
    gfx->words.w0 = 0xE7000000;
    gfx->words.w1 = 0;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0x6000000;
    gfx->words.w1 = (s32)&D_01021970;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xBA001402;
    gfx->words.w1 = 0x200000;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xFD100000;
    gfx->words.w1 = ((obj_t *)arg0)->unk_44;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xF5100000;
    gfx->words.w1 = 0x7058160;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xE6000000;
    gfx->words.w1 = 0;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xF3000000;
    gfx->words.w1 = 0x723F156;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xE7000000;
    gfx->words.w1 = 0;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xF5100C00;
    gfx->words.w1 = 0x58160;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xF2000000;
    gfx->words.w1 = 0x5C05C;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xE7000000;
    gfx->words.w1 = 0;
    gfx = D_800B81E8++;
    gfx->words.w0 = ((((((obj_t *)arg0)->x + 23) << 2) & 4095) << 12) | 0xE4000000 | (((((obj_t *)arg0)->y + 23) << 2) & 4095);
    gfx->words.w1 = (((((obj_t *)arg0)->x << 2) & 4095) << 12) | ((((obj_t *)arg0)->y << 2) & 4095);
    gfx2 = D_800B81E8++;
    gfx2->words.w0 = 0xB4000000;
    gfx2->words.w1 = 0;
    gfx2 = D_800B81E8++;
    gfx2->words.w0 = 0xB3000000;
    gfx2->words.w1 = 0x10000400;
    gfx2 = D_800B81E8++;
    gfx2->words.w0 = 0xE7000000;
    gfx2->words.w1 = 0;
}
