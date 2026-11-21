// StrCat.c -- appends a string

#include "wof.h"

/*
=====================
StrCat

Appends a string.
=====================
*/
u8 *StrCat(u8 *dst, u8 *src) {
    s32 i;
    s32 j;

    i = 0;
    while (dst[i] != 0) {
        i++;
    }
    j = 0;
    while (src[j] != 0) {
        dst[i] = src[j];
        i++;
        j++;
    }
    dst[i] = src[j];
    return dst;
}
