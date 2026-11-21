// wof_cpuletters.c -- the letters the machine may still call, and a letter not in the puzzle
//
// RemoveCalledLetters ends off an 8-byte boundary with PickMissLetter right after, which happens only
// inside an object. Whether InitCpuLetters before it and PickHitLetter after it are this object's the
// text does not say.

#include "wof.h"

/*
=====================
RemoveCalledLetters

Drops from a string the letters already called.
=====================
*/
void RemoveCalledLetters(u8 *letters) {
    u8 *found;
    u8 *p;

    p = letters;
    while (StrLen(p) > 0) {
        found = StrChr(uncalled, *p);
        if (found == 0) {
            StrCopy(p, p + 1);
        } else {
            p++;
        }
    }
}

/*
=====================
PickMissLetter

The last letter of a string that is not in the puzzle, or a space.
=====================
*/
s32 PickMissLetter(u8 *letters) {
    s32 i;
    s32 len;
    u8 result;

    result = 32;
    len = StrLen(letters);
    for (i = 0; i < len; i++) {
        if (CountLetter(letters[i]) == 0) {
            result = letters[i];
            break;
        }
    }
    return result;
}
