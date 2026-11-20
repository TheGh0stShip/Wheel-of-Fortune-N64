#include "wof.h"

typedef struct {
    /* 0x00 */ u8 unk_00[0x10];
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ u8 unk_14[0x30];
    /* 0x44 */ s32 unk_44;
} Sprite;

extern Gfx *D_800B81E8;

void func_80033CF8(s32 arg0, s32 arg1) {
    s32 pad0;
    Gfx *gfx;
    Gfx *gfx2;

    gfx = D_800B81E8++;
    gfx->w0 = 0xE7000000;
    gfx->w1 = 0;
    gfx = D_800B81E8++;
    gfx->w0 = 0x6000000;
    gfx->w1 = (s32)&D_01021970;
    gfx = D_800B81E8++;
    gfx->w0 = 0xBA001402;
    gfx->w1 = 0x200000;
    gfx = D_800B81E8++;
    gfx->w0 = 0xFD100000;
    gfx->w1 = ((Sprite *)arg0)->unk_44;
    gfx = D_800B81E8++;
    gfx->w0 = 0xF5100000;
    gfx->w1 = 0x7094250;
    gfx = D_800B81E8++;
    gfx->w0 = 0xE6000000;
    gfx->w1 = 0;
    gfx = D_800B81E8++;
    gfx->w0 = 0xF3000000;
    gfx->w1 = 0x73FF100;
    gfx = D_800B81E8++;
    gfx->w0 = 0xE7000000;
    gfx->w1 = 0;
    gfx = D_800B81E8++;
    gfx->w0 = 0xF5101000;
    gfx->w1 = 0x94250;
    gfx = D_800B81E8++;
    gfx->w0 = 0xF2000000;
    gfx->w1 = 0x7C07C;
    gfx = D_800B81E8++;
    gfx->w0 = 0xE7000000;
    gfx->w1 = 0;
    gfx = D_800B81E8++;
    gfx->w0 = ((((((Sprite *)arg0)->unk_10 + 31) << 2) & 4095) << 12) | 0xE4000000 | (((((Sprite *)arg0)->unk_12 + 31) << 2) & 4095);
    gfx->w1 = (((((Sprite *)arg0)->unk_10 << 2) & 4095) << 12) | ((((Sprite *)arg0)->unk_12 << 2) & 4095);
    gfx2 = D_800B81E8++;
    gfx2->w0 = 0xB4000000;
    gfx2->w1 = 0;
    gfx2 = D_800B81E8++;
    gfx2->w0 = 0xB3000000;
    gfx2->w1 = 0x10000400;
}
