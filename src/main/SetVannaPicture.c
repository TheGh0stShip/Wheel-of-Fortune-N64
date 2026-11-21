// SetVannaPicture.c -- copies Vanna's picture into this frame, mirrored for -1

#include "wof.h"

/*
=====================
SetVannaPicture

Copies Vanna's picture into this frame, mirrored for -1.
=====================
*/
void SetVannaPicture(s16 *pixels, s32 dir) {
    s32 i;
    s32 j;
    s32 k;
    s32 unused;  /* NOTE: unused in the original */
    u16 *src;
    s16 *dst;

    src = (u16 *)pixels;
    dst = gfxInfo[curGfxInfo].frame.unk_16C00;
    if (dir == -1) {
        for (i = 0; i < 96; i++) {
            k = 63;
            for (j = 0; j < 64; j++) {
                dst[i * 64 + j] = src[i * 64 + k];
                k--;
            }
        }
        return;
    }
    i = 0;
    while (i < 0x1800) {
        dst[i] = src[i];
        i++;
    }
}
