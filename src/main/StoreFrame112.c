// StoreFrame112.c -- copies a decoded frame 112 pixels wide into the frame's picture memory, in the
// tiles DrawMovie112 loads

#include "wof.h"

/*
=====================
StoreFrame112

Copies a decoded frame 112 pixels wide into the frame's picture memory, in the tiles DrawMovie112
loads.
=====================
*/
void StoreFrame112(u16 *pixels) {
    s32 size;
    s32 row;
    s32 col;
    s32 page;
    s32 n;
    u16 *src;
    s16 *dst;
    s32 base;

    base = 0x2000000;
    size = osVirtualToPhysical(gfxInfo[curGfxInfo].frame.unk_19C00);
    size = size - osVirtualToPhysical(&gfxInfo[curGfxInfo].frame);
    src = pixels;
    dst = gfxInfo[curGfxInfo].frame.unk_19C00;
    n = 0;
    page = 0;
    while (page < 2) {
        row = 0;
        while (row < 32) {
            col = 0;
            while (col < 64) {
                dst[page * 3584 + row * 64 + col] = src[n] | 1;
                n++;
                col++;
            }
            col = 0;
            while (col < 48) {
                dst[page * 3584 + 2048 + row * 48 + col] = src[n] | 1;
                n++;
                col++;
            }
            row++;
        }
        page++;
    }
    row = 0;
    while (row < 16) {
        col = 0;
        while (col < 64) {
            (&dst[row * 64 + col])[0x1C00] = src[n] | 1;
            n++;
            col++;
        }
        col = 0;
        while (col < 48) {
            (&dst[row * 48 + col])[0x2000] = src[n] | 1;
            n++;
            col++;
        }
        row++;
    }
}
