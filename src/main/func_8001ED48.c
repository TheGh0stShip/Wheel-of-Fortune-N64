#include "wof.h"

typedef struct {
    /* 0x00000 */ u8 unk_00[0x4];
    /* 0x00004 */ u8 unk_04[0x1E47C];
} Bank;

extern Bank D_800BEF5C[];
extern Bank D_800BEF60[];
extern s32 D_800B61A0;

void func_8001ED48(s32 arg0) {
    s32 sp10;
    s32 y;
    s32 x;
    s32 k;
    s32 n;
    u16 *src;
    s32 pad0;
    s16 *dst;
    s32 pad1[2];
    s32 sp38;

    sp38 = 0x2000000;
    sp10 = func_8003FF78((s32)&D_800BEF5C[D_800B61A0].unk_04[0x19C00]);
    sp10 = sp10 - func_8003FF78((s32)&D_800BEF60[D_800B61A0]);
    src = (u16 *)arg0;
    dst = (s16 *)&D_800BEF5C[D_800B61A0].unk_04[0x19C00];
    n = 0;
    for (k = 0; k < 3; k++) {
        for (y = 0; y < 32; y++) {
            for (x = 0; x < 48; x++) {
                dst[k * 3072 + y * 48 + x] = src[n] | 1;
                (&dst[k * 3072 + y * 48 + x])[1536] = (&src[n])[48] | 1;
                n++;
            }
            n = n + 48;
        }
    }
}
