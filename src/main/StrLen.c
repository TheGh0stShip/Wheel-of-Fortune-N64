// StrLen.c -- the length of a string

#include "wof.h"

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
