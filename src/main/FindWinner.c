#include "wof.h"


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
    func_80029BFC(curPlayer);
}
