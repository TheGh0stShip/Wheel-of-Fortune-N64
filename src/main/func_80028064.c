#include "wof.h"

typedef struct {
    /* 0x00 */ s32 w0;
    /* 0x04 */ s32 w1;
} Gfx;

typedef struct {
    u8 unk_00[0x28];
} Entry;

extern s32 D_01021970;
extern Entry D_8005B710[];
extern Gfx *D_800B81E8;
void func_8002741C(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_80028064(s32 arg0, s32 arg1) {
    s32 pad0[2];
    s32 i;
    s32 pad1;
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
    for (i = 0; i < 22; i++) {
        func_8002741C((s32)&D_8005B710[i], 1, 10, 20);
    }
}
