#include "wof.h"

typedef struct {
    /* 0x00000 */ u8 unk_00[0x4];
    /* 0x00004 */ u8 unk_04[0x1E47C];
} Frame;

extern Frame D_800BEF5C[];
extern u8 D_800BEF60[][0x1E480];

void func_80020C98(s32 arg0) {
    s32 diff;
    s32 i;
    s32 j;
    s32 row;
    s32 n;
    u16 *src;
    s16 *dst;
    s32 *mask;
    s32 bits;
    s32 pad0;
    s32 base;

    base = 0x2000000;
    diff = func_8003FF78(D_800BEF5C[D_800B61A0].unk_04 + 0xAC00);
    diff = diff - func_8003FF78(D_800BEF60[D_800B61A0]);
    src = (u16 *)arg0;
    dst = (s16 *)(D_800BEF5C[D_800B61A0].unk_04 + 0xAC00);
    if (D_800B96A4 != 0) {
        dst = D_800B998C;
        mask = D_800B81E4;
        n = 0x17C0;
        row = 190;
        for (i = 0; i < 96; i++) {
            bits = mask[row];
            for (j = 0; j < 64; j++) {
                if (j == 32) {
                    bits = mask[row + 1];
                }
                if (bits & 0x80000000) {
                    dst[i * 64 + j] = src[n];
                } else {
                    dst[i * 64 + j] = 0;
                }
                n++;
                bits <<= 1;
            }
            row -= 2;
            n -= 128;
        }
        D_800B998C += 0x1800;
        D_800B81E4 += 192;
        return;
    }
    n = 0;
    for (i = 0; i < 64; i++) {
        for (j = 0; j < 32; j++) {
            dst[i * 32 + j] = src[n];
            dst[i * 32 + j + 0x800] = src[n + 32];
            n++;
        }
        n += 32;
    }
}
