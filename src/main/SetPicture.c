// SetPicture.c -- copies a picture into a picture slot of both frames

#include "wof.h"

/*
=====================
SetPicture

Copies a picture into a picture slot of both frames.
=====================
*/
void SetPicture(s16 *pixels, s32 slot) {
    s32 i;
    s32 unused;   /* NOTE: unused in the original */
    s32 unused2;  /* NOTE: unused in the original */
    s32 unused3;  /* NOTE: unused in the original */
    u16 *src;
    s16 *dst1;
    s16 *dst2;

    src = (u16 *)pixels;
    dst1 = gfxInfo[0].frame.unk_0AC00[slot];
    dst2 = gfxInfo[1].frame.unk_0AC00[slot];
    for (i = 0; i < 0x1000; i++) {
        dst1[i] = src[i];
        dst2[i] = src[i];
    }
}
