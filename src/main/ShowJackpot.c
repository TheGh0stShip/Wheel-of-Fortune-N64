// ShowJackpot.c -- lays out the jackpot on the screen in the jackpot round, rolling it when it
// changes

#include "wof.h"

/*
=====================
ShowJackpot

Lays out the jackpot on the screen in the jackpot round, rolling it when it changes.
=====================
*/
void ShowJackpot(void) {
    s32 glyph;
    s32 i;
    s32 len;
    s32 x;
    s32 pos;
    u8 buf[24];
    proc_t *task;

    switch (round) {
    case 2:
        if (shownJackpot == jackpot) {
            return;
        }
        i = 0;
        for (; i < 9; i++) {
            rollingNumberImages[i].x = bigNumberImages[i].x;
            rollingNumberImages[i].width = bigNumberImages[i].width;
            rollingNumberImages[i].texture = bigNumberImages[i].texture;
        }
        i = 0;
        for (; i < 9; i++) {
            bigNumberImages[i].texture = 0;
        }
        x = jackpot;
        IntToStr(buf, x);
        len = StrLen(buf);
        if (len >= 7) {
            len = 6;
        }
        x = 0;
        for (i = 0; i < len; i++) {
            x = x + bigCharWidths[buf[i]];
        }
        x = x + D_8005B170;
        x = x + D_8005B174;
        x = x / 2;
        x = 58 - x;
        pos = 0;
        for (i = 0; i < len + 2; i++) {
            if (i == 0) {
                glyph = 10;
            } else if (i == len - 2) {
                glyph = 11;
            } else {
                glyph = buf[pos++] - '0';
            }
            bigNumberImages[i].x = x;
            bigNumberImages[i].width = bigDigitWidths[glyph];
            bigNumberImages[i].texture = bigDigitTextures[glyph];
            x = x + bigDigitAdvances[glyph];
        }
        if (shownJackpot != 0) {
            task = FindProc(0x6030000, -1);
            if (task != 0) {
                KillProc(task, 0);
            }
            CreatProc(JackpotRollProc, 0x6030000);
        } else {
            for (i = 0; i < 9; i++) {
                rollingNumberImages[i].texture = 0;
                bigNumberImages[i].y = 45;
                bigNumberImages[i].height = 15;
            }
        }
        shownJackpot = jackpot;
    }
}
