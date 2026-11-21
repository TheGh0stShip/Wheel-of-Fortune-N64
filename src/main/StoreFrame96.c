// StoreFrame96.c -- the same for a movie 96 pixels wide

#include "wof.h"

/*
=====================
StoreFrame96

The same for a movie 96 pixels wide.
=====================
*/
void StoreFrame96(u16 *pixels) {
    s32 sp10;
    s32 y;
    s32 x;
    s32 k;
    s32 n;
    u16 *src;
    s32 unused;  /* NOTE: unused in the original */
    s16 *dst;
    s32 unused2;  /* NOTE: unused in the original */
    s32 unused3;  /* NOTE: unused in the original */
    s32 sp38;

    sp38 = 0x2000000;
    sp10 = osVirtualToPhysical(gfxInfo[curGfxInfo].frame.unk_19C00);
    sp10 = sp10 - osVirtualToPhysical(&gfxInfo[curGfxInfo].frame);
    src = pixels;
    dst = gfxInfo[curGfxInfo].frame.unk_19C00;
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
