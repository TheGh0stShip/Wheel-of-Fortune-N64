// FlashPlayerStatus.c -- makes the status pictures of the player whose turn it is flash

#include "wof.h"


/*
=====================
FlashPlayerStatus

Makes the status pictures of the player whose turn it is flash.
=====================
*/
void FlashPlayerStatus(void) {
    s32 i;

    for (i = 0; i < 3; i++) {
        D_8005A4B8[i][0].flash = i == curPlayer;
        D_8005A4B8[i][0].flashLeft = D_8005A4B8[i][0].flashFrames;
        D_8005A4B8[i][1].flash = i == curPlayer;
        D_8005A4B8[i][1].flashLeft = D_8005A4B8[i][1].flashFrames;
    }
}
