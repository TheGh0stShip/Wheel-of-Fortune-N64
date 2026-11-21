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
        playerStatusImages[i][0].flash = i == curPlayer;
        playerStatusImages[i][0].flashLeft = playerStatusImages[i][0].flashFrames;
        playerStatusImages[i][1].flash = i == curPlayer;
        playerStatusImages[i][1].flashLeft = playerStatusImages[i][1].flashFrames;
    }
}
