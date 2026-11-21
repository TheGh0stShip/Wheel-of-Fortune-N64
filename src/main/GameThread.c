#include "wof.h"

/*
=====================
GameThread

The game thread: runs RunFrame forever.
=====================
*/
void GameThread(void *arg) {
    s32 sp10;

    sp10 = 0;
    while (1) {
        RunFrame();
    }
}
