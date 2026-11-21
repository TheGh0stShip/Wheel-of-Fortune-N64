#include "wof.h"


/*
=====================
MustLoseTurn

0 when the player holds a free spin outside the final spin.
=====================
*/
s32 MustLoseTurn(void) {
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    if (players[curPlayer].freeSpin != 0 && finalSpin == 0) {
        return 0;
    }
    return 1;
}
