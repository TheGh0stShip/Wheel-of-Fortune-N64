// GameThread.c -- the game thread: runs RunFrame forever

#include "wof.h"

/*
=====================
GameThread

The game thread: runs RunFrame forever.
=====================
*/
void GameThread(void *arg) {
    s32 zero;  /* NOTE: set to 0 and never read */

    zero = 0;
    while (1) {
        RunFrame();
    }
}
