#include "wof.h"

typedef struct {
    u8 unk_00[0x28];
} Entry;

extern Entry D_8005B710[];
extern Gfx *D_800B81E8;

void func_80028064(s32 arg0, s32 arg1) {
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
    for (i = 0; i < 22; i++) {
        func_8002741C((s32)&D_8005B710[i], 1, 10, 20);
    }
}
