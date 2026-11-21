#include "wof.h"

/*
=====================
CountLetter

How often a letter is in the puzzle; -1 if it was called already.
=====================
*/
s32 CountLetter(register s32 letter) {
    u8 ch;
    s32 i;
    s32 count;
    u8 *p;

    ch = letter;
    p = StrChr(uncalled, ch);
    if (p == 0) {
        return -1;
    }
    count = 0;
    for (i = 0; i < 4; i++) {
        p = puzzleText[i];
        while (p != 0) {
            p = StrChr(p, ch);
            if (p != 0) {
                count++;
                p++;
            }
        }
    }
    return count;
}
