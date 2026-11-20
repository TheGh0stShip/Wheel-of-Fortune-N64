#include "wof.h"

s32 func_800A4CF8(s32 arg0, s32 arg1, s32 arg2) {
    u32 i;
    s8 *dst;

    dst = (s8 *)arg0;
    for (i = 0; i < (u32)arg2; i++) {
        dst[i] = arg1;
    }
    return arg0;
}
