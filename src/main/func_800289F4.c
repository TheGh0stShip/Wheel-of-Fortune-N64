#include "wof.h"

typedef struct {
    /* 0x00 */ s32 w0;
    /* 0x04 */ s32 w1;
} Gfx;

typedef struct {
    u8 unk_00[0x28];
} Sprite;

extern s32 D_01021970;
extern Sprite D_8005A760[];
extern Gfx *D_800B81E8;
void func_800278A8(s32 arg0, s32 arg1);

void func_800289F4(s32 arg0, s32 arg1) {
    s32 i;
    Gfx *gfx;

    gfx = D_800B81E8++;
    gfx->w0 = 0xE7000000;
    gfx->w1 = 0;
    gfx = D_800B81E8++;
    gfx->w0 = 0x6000000;
    gfx->w1 = (s32)&D_01021970;
    gfx = D_800B81E8++;
    gfx->w0 = 0xBA001402;
    gfx->w1 = 0x200000;
    for (i = 0; i < 2; i++) {
        func_800278A8((s32)&D_8005A760[i], 1);
    }
}
