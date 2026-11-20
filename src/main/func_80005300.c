#include "wof.h"

extern Gfx *D_800B81E8;

void func_80005300(s32 arg0) {
    Gfx *gfx;

    switch (arg0) {
    case 1:
        gfx = D_800B81E8++;
        gfx->words.w0 = 0xBC00000A;
        gfx->words.w1 = 0x505050FF;
        gfx = D_800B81E8++;
        gfx->words.w0 = 0xBC00040A;
        gfx->words.w1 = 0x505050FF;
        return;
    case 2:
        gfx = D_800B81E8++;
        gfx->words.w0 = 0xBC00200A;
        gfx->words.w1 = 0x8C8C8CFF;
        gfx = D_800B81E8++;
        gfx->words.w0 = 0xBC00240A;
        gfx->words.w1 = 0x8C8C8CFF;
        return;
    case 3:
        gfx = D_800B81E8++;
        gfx->words.w0 = 0xBC00400A;
        gfx->words.w1 = 0x8C8C8CFF;
        gfx = D_800B81E8++;
        gfx->words.w0 = 0xBC00440A;
        gfx->words.w1 = 0x8C8C8CFF;
        return;
    case 4:
        gfx = D_800B81E8++;
        gfx->words.w0 = 0xBC00600A;
        gfx->words.w1 = 0x8C8C8CFF;
        gfx = D_800B81E8++;
        gfx->words.w0 = 0xBC00640A;
        gfx->words.w1 = 0x8C8C8CFF;
        return;
    case 5:
        gfx = D_800B81E8++;
        gfx->words.w0 = 0xBC00800A;
        gfx->words.w1 = 0x8C8C8CFF;
        gfx = D_800B81E8++;
        gfx->words.w0 = 0xBC00840A;
        gfx->words.w1 = 0x8C8C8CFF;
        return;
    case 6:
        gfx = D_800B81E8++;
        gfx->words.w0 = 0xBC00A00A;
        gfx->words.w1 = 0x141414FF;
        gfx = D_800B81E8++;
        gfx->words.w0 = 0xBC00A40A;
        gfx->words.w1 = 0x141414FF;
        return;
    }
}
