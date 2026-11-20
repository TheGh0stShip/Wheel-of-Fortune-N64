#include "wof.h"

void GameThread(void *arg) {
    s32 sp10;

    sp10 = 0;
    while (1) {
        RunFrame();
    }
}
