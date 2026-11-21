// wof_str.c -- strings and numbers: copying, appending, finding and measuring strings, a number as a
// string, random numbers, the absolute value, printing a number, the fatal error and printing a string
//
// The object lies between the 4-byte gaps that end NextPlayer and PrintStr. StrNCopy, StrChr and
// SeedRandom each end off an 8-byte boundary with the next function right after, which
// happens only inside an object. guess: the joins after StrCat, StrCopy, StrLen, IntToStr, Random, Abs,
// PrintNum and FatalError. The zero word before 0x800007D8 opens the read-only data of an object starting
// after NextPlayer, StrCat, StrCopy or StrLen; the gap after NextPlayer is one of them and an object
// starts there for certain, so the start takes it, and the project's ruling takes the join everywhere
// else.

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

/*
=====================
StrCopy

Copies a string.
=====================
*/
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

/*
=====================
IntToStr

Writes a number in decimal.
=====================
*/
void IntToStr(u8 *dst, s32 value) {
    s32 i;
    u8 buf[24];

    if (value == 0) {
        StrCopy(dst, "0");
        return;
    }
    i = 19;
    buf[i--] = 0;
    while (i >= 0) {
        buf[i] = Abs(value % 10) + '0';
        i--;
        value = value / 10;
    }
    i = 0;
    while (buf[i] == '0' && i < 20) {
        i++;
    }
    *dst = 0;
    if (value < 0) {
        StrCopy(dst, "-");
    }
    StrCopy(dst, &buf[i]);
}

/*
=====================
Random

GuRandom() modulo its argument.
=====================
*/
s32 Random(s32 range) {
    return guRandom() % range;
}

/*
=====================
SeedRandom

Empty, and nothing calls it. guess: the seed function that goes with Random, which draws from
guRandom's own sequence and has nothing to seed.
=====================
*/
void SeedRandom(s32 seed) {
}

/*
=====================
Abs

The absolute value.
=====================
*/
s32 Abs(s32 value) {
    if (value < 0) {
        value = value * -1;
    }
    return value;
}

/*
=====================
PrintNum

Writes a number in decimal and prints it with PrintStr.
=====================
*/
void PrintNum(s32 num) {
    u8 buf[20];
    s32 i;
    s32 divisor;
    s32 digit;
    s32 value;

    value = num;
    if (value < 0) {
        value = value * -1;
    }
    buf[19] = 0;
    i = 18;
    for (divisor = 10; divisor <= 999999999; divisor = divisor * 10) {
        digit = value % divisor;
        value = value - digit;
        digit = digit / (divisor / 10);
        buf[i--] = digit + '0';
        if (value == 0) {
            break;
        }
    }
    if (num < 0) {
        buf[i--] = '-';
    }
    PrintStr(&buf[i + 1]);
}

/*
=====================
FatalError

Prints "ERROR: " and the message, then loops forever.
=====================
*/
void FatalError(char *msg) {
    PrintStr("ERROR: ");
    PrintStr(msg);
    PrintStr("\n");
    for (;;) {
    }
}

/*
=====================
PrintStr

The debug print, which in retail only measures its string.
=====================
*/
void PrintStr(u8 *str) {
    s32 len;

    len = StrLen(str);
}
