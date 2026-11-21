#include "wof.h"


void FlashScore(s32 player) {
    s32 i;

    for (i = 0; i < 7; i++) {
        D_8005ADD0[player][i].unk_10 = 1;
    }
}
