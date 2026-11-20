#include "wof.h"

void func_80029974(s32 arg0) {
    s32 i;
    s32 j;
    s32 len;
    s32 value;
    s32 unused;  /* NOTE: unused in the original */
    u8 buf[24];

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 7; j++) {
            D_8005ADD0[i][j].unk_20 = 0;
        }
        if (arg0 != 0) {
            value = players[i].unk_004;
        } else {
            value = players[i].unk_000;
        }
        IntToStr(buf, value);
        len = StrLen(buf);
        if (len >= 7) {
            len = 6;
        }
        D_8005ADD0[i][6 - len].unk_20 = D_01010FA0;
        for (j = 0; j < len; j++) {
            D_8005ADD0[i][j + 7 - len].unk_20 = D_8005ACE8[buf[j]];
        }
    }
    SetScoreDigits(arg0);
}
