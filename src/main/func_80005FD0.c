#include "wof.h"

void func_80005FD0(s32 arg0) {
    s32 pad0;
    Gfx *gfx;

    gfx = D_800B81E8++;
    gfx->words.w0 = 0xE7000000;
    gfx->words.w1 = 0;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xED000000;
    gfx->words.w1 = 0x5003C0;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xE7000000;
    gfx->words.w1 = 0;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xE7000000;
    gfx->words.w1 = 0;
}
