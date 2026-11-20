#include "wof.h"

void func_8003143C(s16 *arg0, s32 arg1) {
    s32 i;
    s32 j;
    s32 k;
    s32 unused;  /* NOTE: unused in the original */
    u16 *src;
    s16 *dst;

    src = (u16 *)arg0;
    dst = D_800BEF08[D_800B61A0].frame.unk_16C00;
    if (arg1 == -1) {
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
