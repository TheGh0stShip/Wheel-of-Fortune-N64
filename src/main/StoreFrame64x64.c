#include "wof.h"

/*
=====================
StoreFrame64x64

The same for a movie of 64 by 64.
=====================
*/
void StoreFrame64x64(u16 *arg0) {
    s32 diff;
    s32 i;
    s32 j;
    s32 row;
    s32 n;
    u16 *src;
    s16 *dst;
    s32 *mask;
    s32 bits0;
    s32 bits1;
    s32 base;

    base = 0x2000000;
    diff = osVirtualToPhysical(gfxInfo[curGfxInfo].frame.unk_0AC00[0]);
    diff = diff - osVirtualToPhysical(&gfxInfo[curGfxInfo].frame);
    src = arg0;
    dst = gfxInfo[curGfxInfo].frame.unk_0AC00[0];
    if (movieToMemory != 0) {
        dst = D_800B998C;
        mask = D_800B81E4;
        n = 4032;
        row = 126;
        for (i = 0; i < 64; i++) {
            bits0 = mask[row];
            bits1 = mask[row + 1];
            for (j = 0; j < 32; j++) {
                if (bits0 & 0x80000000) {
                    dst[i * 32 + j] = src[n];
                } else {
                    dst[i * 32 + j] = 0;
                }
                if (bits1 & 0x80000000) {
                    dst[i * 32 + j + 0x800] = src[n + 32];
                } else {
                    dst[i * 32 + j + 0x800] = 0;
                }
                bits0 <<= 1;
                bits1 <<= 1;
                n++;
            }
            row -= 2;
            n -= 96;
        }
        D_800B998C += 0x1000;
        D_800B81E4 += 128;
        return;
    }
    dst = gfxInfo[curGfxInfo].frame.unk_19C00;
    row = 0;
    n = 0;
    mask = D_800B81E4;
    for (i = 0; i < 64; i++) {
        bits0 = mask[row++];
        bits1 = mask[row++];
        for (j = 0; j < 32; j++) {
            if (bits0 & 0x80000000) {
                dst[i * 32 + j] = src[n];
            } else {
                dst[i * 32 + j] = 0;
            }
            if (bits1 & 0x80000000) {
                dst[i * 32 + j + 0x800] = src[n + 32];
            } else {
                dst[i * 32 + j + 0x800] = 0;
            }
            bits0 <<= 1;
            bits1 <<= 1;
            n++;
        }
        n += 32;
    }
    D_800B81E4 += 128;
}
