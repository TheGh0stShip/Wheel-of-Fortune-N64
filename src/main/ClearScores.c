#include "wof.h"


void ClearScores(void) {
    s32 i;

    players[0].unk_000 = 0;
    players[0].unk_004 = 0;
    players[0].unk_0F8 = 0;
    for (i = 0; i < 10; i++) {
        StrCopy(players[0].unk_030[i], "0");
    }
    players[1].unk_000 = 0;
    players[1].unk_004 = 0;
    players[1].unk_0F8 = 0;
    for (i = 0; i < 10; i++) {
        StrCopy(players[1].unk_030[i], "0");
    }
    players[2].unk_000 = 0;
    players[2].unk_004 = 0;
    players[2].unk_0F8 = 0;
    for (i = 0; i < 10; i++) {
        StrCopy(players[2].unk_030[i], "0");
    }
}
