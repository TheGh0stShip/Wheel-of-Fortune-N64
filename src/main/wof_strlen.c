// wof_strlen.c -- finding a character in a string and the length of a string
//
// StrChr ends off an 8-byte boundary with StrLen right after, which happens only inside an object.
// Whether StrCopy before it and IntToStr after it are this object's the text does not say.

#include "wof.h"

/*
=====================
StrChr

Finds a character in a string, or 0.
=====================
*/
u8 *StrChr(u8 *str, s32 c) {
    s32 i;

    i = 0;
    while (str[i] != 0 && str[i] != c) {
        i++;
    }
    if (str[i] == 0) {
        return 0;
    }
    return str + i;
}

/*
=====================
StrLen

The length of a string.
=====================
*/
s32 StrLen(u8 *str) {
    s32 len;

    len = 0;
    while (str[len] != 0) {
        len++;
    }
    return len;
}
