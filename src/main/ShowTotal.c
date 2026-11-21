#include "wof.h"


/*
=====================
ShowTotal

Lays out the player's total in the middle of the screen.
=====================
*/
void ShowTotal(void) {
    s32 glyph;
    s32 i;
    s32 len;
    s32 x;
    s32 pos;
    u8 buf[32];

    for (i = 0; i < 9; i++) {
        D_8005B4C8[i].texture = 0;
    }
    x = players[curPlayer].total;
    IntToStr(buf, x);
    len = StrLen(buf);
    if (len >= 7) {
        len = 6;
    }
    x = 0;
    for (i = 0; i < len; i++) {
        x = x + D_8005B088[buf[i]];
    }
    x = x + D_8005B170;
    x = x + D_8005B174;
    x = x / 2;
    x = 160 - x;
    pos = 0;
    for (i = 0; i < len + 2; i++) {
        if (i == 0) {
            glyph = 10;
        } else if (i == len - 2) {
            glyph = 11;
        } else {
            glyph = buf[pos++] - 48;
        }
        D_8005B4C8[i].x = x;
        D_8005B4C8[i].width = D_8005B178[glyph];
        D_8005B4C8[i].texture = D_8005B118[glyph];
        x = x + D_8005B148[glyph];
    }
    i = 0;
    while (i < 9) {
        D_8005B4C8[i].y = 112;
        D_8005B4C8[i].height = 15;
        i++;
    }
}
