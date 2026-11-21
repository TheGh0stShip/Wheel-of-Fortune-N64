// FindWinner.c -- the player with the most money takes the turn and is shown

#include "wof.h"


/*
=====================
FindWinner

The player with the most money takes the turn and is shown.
=====================
*/
void FindWinner(void) {
    s32 i;
    s32 max;

    max = 0;
    curPlayer = 0;
    for (i = 0; i < 3; i++) {
        if (players[i].total > max) {
            max = players[i].total;
            curPlayer = i;
        }
    }
    UnlightPlayers();
    FlashScore(curPlayer);
}
