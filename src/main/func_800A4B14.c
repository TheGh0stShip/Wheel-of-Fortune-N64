#include "wof.h"

s32 func_800A4B14(s32 arg0, s32 arg1, s32 arg2) {
    u32 i;
    s8 *dst;
    u8 *src;

    dst = (s8 *)arg0;
    src = (u8 *)arg1;
    for (i = 0; i < (u32)arg2; i++) {
        dst[i] = src[i];
    }
    return arg0;
}
