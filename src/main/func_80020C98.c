#include "wof.h"

void func_80020C98(u16 *arg0) {
    s32 diff;
    s32 i;
    s32 j;
    s32 row;
    s32 n;
    u16 *src;
    s16 *dst;
    s32 *mask;
    s32 bits;
    s32 unused;  /* NOTE: unused in the original */
    s32 base;

    base = 0x2000000;
    diff = osVirtualToPhysical(gfxInfo[curGfxInfo].frame.unk_0AC00[0]);
    diff = diff - osVirtualToPhysical(&gfxInfo[curGfxInfo].frame);
    src = arg0;
    dst = gfxInfo[curGfxInfo].frame.unk_0AC00[0];
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
