// InitPlayers.c -- a turn proc for each contestant, a person's or the machine's

#include "wof.h"

/*
=====================
InitPlayers

A turn proc for each contestant, a person's or the machine's.
=====================
*/
void InitPlayers(void) {
    s32 unused;  /* NOTE: unused in the original */
    s32 unused2;  /* NOTE: unused in the original */
    s32 i;

    InitCpuLetters();
    for (i = 0; i < 3; i++) {
        if (gameMode == 3) {
            AddDemoCpu(i);
        } else if (players[i].controller < 4) {
            AddPlayer(i);
        } else {
            AddCpu(i);
        }
        cameraTurn[i][0] = 0;
        cameraTurn[i][1] = 0;
    }
    if (gameMode == 3) {
        SetGameView(17, 0);
        return;
    }
    SetGameView(3, 0);
}
