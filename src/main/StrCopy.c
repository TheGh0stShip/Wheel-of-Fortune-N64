#include "wof.h"

u8 *StrCopy(u8 *dst, u8 *src) {
    s32 i;

    i = 0;
    while (src[i] != 0) {
        dst[i] = src[i];
        i++;
    }
    dst[i] = src[i];
    return dst;
}
