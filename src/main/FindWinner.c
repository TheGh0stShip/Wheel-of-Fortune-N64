#include "wof.h"


void FindWinner(void) {
    s32 i;
    s32 max;

    max = 0;
    curPlayer = 0;
    for (i = 0; i < 3; i++) {
        if (players[i].unk_004 > max) {
            max = players[i].unk_004;
            curPlayer = i;
        }
    }
    UnlightPlayers();
    func_80029BFC(curPlayer);
}
