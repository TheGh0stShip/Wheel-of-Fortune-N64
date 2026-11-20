#include "wof.h"

typedef struct {
    u8 unk_00[0x28];
} Entry;

extern Entry D_8005A620[];
extern Gfx *D_800B81E8;

void func_800288CC(s32 arg0, s32 arg1) {
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
    for (i = 0; i < 8; i++) {
        func_800278A8((s32)&D_8005A620[i], 1);
    }
}
