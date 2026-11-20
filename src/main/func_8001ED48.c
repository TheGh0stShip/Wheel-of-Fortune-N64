#include "wof.h"

void func_8001ED48(s32 arg0) {
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
    sp10 = osVirtualToPhysical(D_800BEF08[D_800B61A0].frame.unk_19C00);
    sp10 = sp10 - osVirtualToPhysical(&D_800BEF08[D_800B61A0].frame);
    src = (u16 *)arg0;
    dst = D_800BEF08[D_800B61A0].frame.unk_19C00;
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
