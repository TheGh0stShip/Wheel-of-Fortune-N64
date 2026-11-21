// SetScorePictures.c -- lays out the digit pictures of each player's score on the screen, and on
// the stage

#include "wof.h"

/*
=====================
SetScorePictures

Lays out the digit pictures of each player's score on the screen, and on the stage.
=====================
*/
void SetScorePictures(s32 total) {
    s32 i;
    s32 j;
    s32 len;
    s32 value;
    s32 unused;  /* NOTE: unused in the original */
    u8 buf[24];

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 7; j++) {
            statusScoreImages[i][j].texture = 0;
        }
        if (total != 0) {
            value = players[i].total;
        } else {
            value = players[i].score;
        }
        IntToStr(buf, value);
        len = StrLen(buf);
        if (len >= 7) {
            len = 6;
        }
        statusScoreImages[i][6 - len].texture = D_01010FA0;
        for (j = 0; j < len; j++) {
            statusScoreImages[i][j + 7 - len].texture = statusDigitTextures[buf[j]];
        }
    }
    SetScoreDigits(total);
}
