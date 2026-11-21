// PickMissLetter.c -- the last letter of a string that is not in the puzzle, or a space

#include "wof.h"

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
