// StrChr.c -- finds a character in a string, or 0

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
