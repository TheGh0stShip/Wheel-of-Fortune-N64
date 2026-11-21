// FlashScore.c -- makes a player's score on the screen flash

#include "wof.h"


/*
=====================
FlashScore

Makes a player's score on the screen flash.
=====================
*/
void FlashScore(s32 player) {
    s32 i;

    for (i = 0; i < 7; i++) {
        D_8005ADD0[player][i].flash = 1;
    }
}
