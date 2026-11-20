#include "wof.h"

void func_80013500(s32 arg0) {
    s32 i;
    s32 j;
    s32 len;
    s32 value;
    s32 unused;  /* NOTE: unused in the original */
    u8 digits[24];

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 8; j++) {
            D_800BEEA8[i][j] = (s32)&D_010367A8;
        }
        if (arg0 != 0) {
            value = D_800B9990[i].unk_004;
        } else {
            value = D_800B9990[i].unk_000;
        }
        func_80009AE0((s32)digits, value);
        len = func_80009A74((s32)digits);
        if (len >= 8) {
            len = 7;
        }
        D_800BEEA8[i][7 - len] = (s32)&D_01035FA8;
        for (j = 0; j < len; j++) {
            D_800BEEA8[i][j + 8 - len] = D_80057A68[digits[j]];
        }
    }
}
