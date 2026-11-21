// wof_strcat.c -- copying n characters and appending a string
//
// StrNCopy ends off an 8-byte boundary with StrCat right after, which happens only inside an object.
// The object starts after the 4-byte gap that ends NextPlayer; whether it runs on after StrCat the text
// does not say.

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
