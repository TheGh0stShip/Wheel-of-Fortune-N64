#include "wof.h"

/*
=====================
NextPlayer

Passes the turn to the next player, or for a new round to the round's first.
=====================
*/
void NextPlayer(s32 newRound) {
    D_800B9980 = 0;
    jackpotWon = 0;
    if (newRound == 0) {
        if (CheckSolved(0) == 2) {
            canSpin = 0;
        } else {
            canSpin = 1;
        }
        canBuyVowel = 1;
        canSolve = 1;
        curPlayer++;
        if (curPlayer >= 3) {
            curPlayer = 0;
        }
        return;
    }
    curPlayer = round % 3;
}
