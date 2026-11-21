#include "wof.h"


/*
=====================
ResetGame

Sets the round and the player to the first, clears the scores and starts the first round.
=====================
*/
void ResetGame(void) {
    round = 0;
    D_800B9538 = 0;
    if (gameMode == 3) {
        round = 2;
        curPlayer = 2;
    } else {
        curPlayer = 0;
    }
    finalSpin = 0;
    players[0].freeSpin = 0;
    players[1].freeSpin = 0;
    players[2].freeSpin = 0;
    ClearScores();
    StartRound();
}
