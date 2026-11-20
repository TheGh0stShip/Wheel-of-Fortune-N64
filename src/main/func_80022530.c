#include "wof.h"

typedef struct {
    u8 unk_00[0x28];
} Model;

extern Model D_80059008[];
extern Model D_80059120[];
extern Gfx *D_800B81E8;

void func_80022530(s32 arg0, s32 arg1) {
    s32 pad0[2];
    s32 i;
    s32 pad1;
    Gfx *gfx;

    gfx = D_800B81E8++;
    gfx->words.w0 = 0xE7000000;
    gfx->words.w1 = 0;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0x6000000;
    gfx->words.w1 = (u32)&D_01021970;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xBA001402;
    gfx->words.w1 = 0x200000;
    i = 0;
    for (;;) {
        if (i >= 118) {
            break;
        }
        func_800278A8((s32)&D_80059120[i], 1);
        i++;
    }
    i = 0;
    for (;;) {
        if (i >= 7) {
            return;
        }
        func_800278A8((s32)&D_80059008[i], 1);
        i++;
    }
}
