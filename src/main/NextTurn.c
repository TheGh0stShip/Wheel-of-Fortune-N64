#include "wof.h"

void NextTurn(void) {
    proc_t *handle;

    NextPlayer(0);
    LightPlayer(curPlayer);
    handle = FindProc(curPlayer | 0x2000000, 0xFF0000FF);
    ProcPostMessage(handle, 1, 0);
    handle = FindProc(0x5000000, -1);
    ProcPostMessage(handle, 1, 0);
    return;
}
