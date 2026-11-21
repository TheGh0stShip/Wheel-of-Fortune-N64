#include "wof.h"


/*
=====================
ClearScores

Sets every player's scores to 0.
=====================
*/
void ClearScores(void) {
    s32 i;

    players[0].score = 0;
    players[0].total = 0;
    players[0].prize = 0;
    for (i = 0; i < 10; i++) {
        StrCopy(players[0].unk_030[i], "0");
    }
    players[1].score = 0;
    players[1].total = 0;
    players[1].prize = 0;
    for (i = 0; i < 10; i++) {
        StrCopy(players[1].unk_030[i], "0");
    }
    players[2].score = 0;
    players[2].total = 0;
    players[2].prize = 0;
    for (i = 0; i < 10; i++) {
        StrCopy(players[2].unk_030[i], "0");
    }
}
