#include "wof.h"

void func_80031340(s32 arg0, s32 arg1) {
    s32 i;
    s32 unused;   /* NOTE: unused in the original */
    s32 unused2;  /* NOTE: unused in the original */
    s32 unused3;  /* NOTE: unused in the original */
    u16 *src;
    s16 *dst1;
    s16 *dst2;

    src = (u16 *)arg0;
    dst1 = D_800C9B60[arg1];
    dst2 = D_800E7FE0[arg1];
    for (i = 0; i < 0x1000; i++) {
        dst1[i] = src[i];
        dst2[i] = src[i];
    }
}
