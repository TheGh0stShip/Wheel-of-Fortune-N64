#include "wof.h"


s32 func_80017728(void) {
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    if (players[curPlayer].unk_008 != 0 && finalSpin == 0) {
        return 0;
    }
    return 1;
}
