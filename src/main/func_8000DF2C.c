#include "wof.h"

extern Gfx *D_800B81E8;

void func_8000DF2C(s32 arg0, s32 arg1) {
    s32 pad0[2];
    s32 row;
    s32 col;
    Gfx *gfx;
    Gfx *gfx2;

    gfx = D_800B81E8++;
    gfx->words.w0 = 0x6000000;
    gfx->words.w1 = (s32)&D_01021970;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xBA001402;
    gfx->words.w1 = 0x200000;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xBA000E02;
    gfx->words.w1 = 0x8000;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xFD100000;
    gfx->words.w1 = (s32)&D_01146E68;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xE8000000;
    gfx->words.w1 = 0;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xF5000100;
    gfx->words.w1 = 0x7000000;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xE6000000;
    gfx->words.w1 = 0;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xF0000000;
    gfx->words.w1 = 0x703C000;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xE7000000;
    gfx->words.w1 = 0;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xE7000000;
    gfx->words.w1 = 0;
    for (row = 0; row < 2; row++) {
        for (col = 0; col < 3; col++) {
            gfx = D_800B81E8++;
            gfx->words.w0 = 0xFD500000;
            gfx->words.w1 = D_80057970[row][col];
            gfx = D_800B81E8++;
            gfx->words.w0 = 0xF5500000;
            gfx->words.w1 = 0x7040100;
            gfx = D_800B81E8++;
            gfx->words.w0 = 0xE6000000;
            gfx->words.w1 = 0;
            gfx = D_800B81E8++;
            gfx->words.w0 = 0xF3000000;
            gfx->words.w1 = 0x73FF200;
            gfx = D_800B81E8++;
            gfx->words.w0 = 0xE7000000;
            gfx->words.w1 = 0;
            gfx = D_800B81E8++;
            gfx->words.w0 = 0xF5400800;
            gfx->words.w1 = 0x40100;
            gfx = D_800B81E8++;
            gfx->words.w0 = 0xF2000000;
            gfx->words.w1 = 0xFC0FC;
            gfx = D_800B81E8++;
            gfx->words.w0 = 0xE7000000;
            gfx->words.w1 = 0;
            gfx = D_800B81E8++;
            gfx->words.w0 = ((((((obj_t *)arg0)->x + col * 64 + 63) << 2) & 4095) << 12) | 0xE4000000 | (((((obj_t *)arg0)->y + row * 64 + 63) << 2) & 4095);
            gfx->words.w1 = (((((obj_t *)arg0)->x + col * 64) << 2 & 4095) << 12) | ((((obj_t *)arg0)->y + row * 64) << 2 & 4095);
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
    }
}
