#include "wof.h"


/*
=====================
ShowLetter

Puts a letter on the board wherever the puzzle has it.
=====================
*/
void ShowLetter(register s32 letter) {
    u8 ch;
    s32 i;
    u8 *p;

    ch = letter;
    for (i = 0; i < 4; i++) {
        p = puzzleText[i];
        while (p != 0) {
            p = StrChr(p, ch);
            if (p != 0) {
                board[i][(p - puzzleText[0]) - i * 21] = ch;
                p++;
            }
        }
    }
}
