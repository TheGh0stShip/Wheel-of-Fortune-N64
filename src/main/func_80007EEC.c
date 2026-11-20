#include "wof.h"

typedef struct {
    /* 0x000 */ s32 unk_000;
    /* 0x004 */ s32 unk_004;
    /* 0x008 */ u8 unk_008[0xF0];
    /* 0x0F8 */ s32 unk_0F8;
    /* 0x0FC */ u8 unk_0FC[0x18];
} Player;

extern Player D_800B9990[];
extern s32 D_800B9540;
extern u8 D_800B9559[][21];
extern u8 D_800B9601[][21];
extern s32 D_800B96A0;
extern s32 D_800B999C;
extern s32 D_800B9AB0;
extern s32 D_800B9BC4;
extern s32 D_800B9CF8;
extern s32 D_800FB808;

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
            p = (u8 *)func_800099B0((s32)p, 43);
            if (p != 0) {
                c = D_800B9601[row][(s32)p - (s32)D_800B9559 - row * 21];
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
        D_800B999C = 0;
        D_800B9AB0 = 0;
        D_800B9BC4 = 0;
    }
    return 1;
}
