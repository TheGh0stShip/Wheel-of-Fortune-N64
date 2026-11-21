// wof_nextround.c -- whether a player must lose the turn, and the next round
//
// MustLoseTurn ends off an 8-byte boundary with NextRound right after, which happens only inside an
// object. Whether NextTurn before it and FindWinner after it are this object's the text does not say.

#include "wof.h"

/*
=====================
MustLoseTurn

0 when the player holds a free spin outside the final spin.
=====================
*/
s32 MustLoseTurn(void) {
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    if (players[curPlayer].freeSpin != 0 && finalSpin == 0) {
        return 0;
    }
    return 1;
}

/*
=====================
NextRound

Starts the next round.
=====================
*/
void NextRound(void) {
    proc_t *handle;

    NextPlayer(1);
    StartRound();
    LightPlayer(curPlayer);
    handle = FindProc(curPlayer | 0x02000000, 0xFF0000FF);
    ProcPostMessage(handle, 0xF, 0);
    ProcPostEvent(0xF);
    InitBoard();
    InitCpuLetters();
}
