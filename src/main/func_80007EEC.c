#include "wof.h"


s32 func_80007EEC(s32 arg0) {
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
    if (consonants > 0) {
        return 0;
    }
    if (consonants == 0 && vowels > 0) {
        D_800B9CF8 = 0;
        return 2;
    }
    if (arg0 != 0) {
        if (D_800B96A0 != 0) {
            func_80034950();
            D_800B9990[D_800FB808].unk_000 += D_800B9540;
        }
        if (D_800B9990[D_800FB808].unk_000 < 500) {
            D_800B9990[D_800FB808].unk_000 = 500;
        }
        D_800B9990[D_800FB808].unk_004 += D_800B9990[D_800FB808].unk_000;
        D_800B9990[D_800FB808].unk_004 += D_800B9990[D_800FB808].unk_0F8;
        D_800B9990[0].unk_00C = 0;
        D_800B9990[1].unk_00C = 0;
        D_800B9990[2].unk_00C = 0;
    }
    return 1;
}
