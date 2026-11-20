#include "wof.h"


s32 func_800082E4(void) {
    s32 row;
    s32 consonants;
    s32 vowels;
    u8 *p;
    u8 c;

    vowels = 0;
    consonants = 0;
    for (row = 0; row < 4; row++) {
        p = D_800B9559[row];
        while (p != 0) {
            p = StrChr(p, 43);
            if (p != 0) {
                c = D_800B9601[row][p - D_800B9559[0] - row * 21];
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
