// GetHiddenKinds.c -- which kinds of letters the board still hides: 4 both, 3 consonants, 2 vowels,
// 1 none

#include "wof.h"


/*
=====================
GetHiddenKinds

Which kinds of letters the board still hides: 4 both, 3 consonants, 2 vowels, 1 none.
=====================
*/
s32 GetHiddenKinds(void) {
    s32 row;
    s32 consonants;
    s32 vowels;
    u8 *p;
    u8 c;

    vowels = 0;
    consonants = 0;
    for (row = 0; row < 4; row++) {
        p = board[row];
        while (p != 0) {
            p = StrChr(p, 43);
            if (p != 0) {
                c = puzzleText[row][p - board[0] - row * 21];
                switch (c) {
                case 'A':
                case 'E':
                case 'I':
                case 'O':
                case 'U':
                    vowels++;
                    break;
                default:
                    consonants++;
                }
                p++;
            }
        }
    }
    if (consonants > 0 && vowels > 0) {
        return 4;
    }
    if (consonants == 0 && vowels > 0) {
        return 2;
    }
    if (consonants > 0 && vowels == 0) {
        return 3;
    }
    return 1;
}
