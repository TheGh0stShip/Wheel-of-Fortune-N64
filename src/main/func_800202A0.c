#include "wof.h"

void func_800202A0(s32 arg0) {
    s32 size;
    s32 row;
    s32 col;
    s32 page;
    s32 n;
    u16 *src;
    s16 *dst;
    s32 sp2C;

    sp2C = 0x2000000;
    size = osVirtualToPhysical(D_800BEF08[D_800B61A0].frame.unk_19C00);
    size = size - osVirtualToPhysical(&D_800BEF08[D_800B61A0].frame);
    src = (u16 *)arg0;
    dst = D_800BEF08[D_800B61A0].frame.unk_19C00;
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
