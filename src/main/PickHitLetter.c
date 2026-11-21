#include "wof.h"

/*
=====================
PickHitLetter

The last letter of a string that is in the puzzle, or else PickMissLetter's.
=====================
*/
s32 PickHitLetter(u8 *letters) {
    s32 i;
    s32 len;
    u8 c;

    c = ' ';
    len = StrLen(letters);
    for (i = 0; i < len; i++) {
        if (CountLetter(letters[i]) > 0) {
            c = letters[i];
            break;
        }
    }
    if (c == ' ') {
        c = PickMissLetter(letters);
    }
    return c;
}
