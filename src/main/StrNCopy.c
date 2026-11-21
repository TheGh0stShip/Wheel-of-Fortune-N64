// StrNCopy.c -- copies n characters, repeating the source's end once it is reached

#include "wof.h"

/*
=====================
StrNCopy

Copies n characters, repeating the source's end once it is reached.
=====================
*/
u8 *StrNCopy(u8 *dst, u8 *src, s32 n) {
    s32 i;
    s32 j;

    i = 0;
    j = 0;
    while (i < n) {
        dst[i] = src[j];
        if (src[j] != 0) {
            j++;
        }
        i++;
    }
    return dst;
}
