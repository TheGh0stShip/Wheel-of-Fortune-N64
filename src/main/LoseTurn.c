// LoseTurn.c -- the turn passes, unless the player holds a free spin, who is asked (message 37) and
// keeps it

#include "wof.h"


/*
=====================
LoseTurn

The turn passes, unless the player holds a free spin, who is asked (message 37) and keeps it.
=====================
*/
s32 LoseTurn(void) {
    proc_t *handle;

    if (players[curPlayer].freeSpin != 0 && finalSpin == 0) {
        ProcPostMessageClass(37, curPlayer | 0x2000000, 0xFF0000FF, 1);
        return 0;
    }
    NextPlayer(0);
    LightPlayer(curPlayer);
    handle = FindProc(curPlayer | 0x2000000, 0xFF0000FF);
    ProcPostMessage(handle, 1, 0);
    handle = FindProc(0x5000000, -1);
    ProcPostMessage(handle, 1, 0);
    return 1;
}
