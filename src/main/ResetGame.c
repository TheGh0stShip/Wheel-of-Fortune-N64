#include "wof.h"


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
    players[0].unk_008 = 0;
    players[1].unk_008 = 0;
    players[2].unk_008 = 0;
    ClearScores();
    StartRound();
}
