// NextRound.c -- starts the next round

#include "wof.h"

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
