#include "wof.h"

void ApplyWedge(s32 final) {
    if (final != 0) {
        finalSpinValue = GetWedgeValue();
    } else {
        if (GetWedgeValue() == -1) {
            players[curPlayer].score = 0;
            players[curPlayer].prize = 0;
            players[curPlayer].hasPrize = 0;
        }
        if (round == 2) {
            if (GetWedgeValue() > 0) {
                jackpot += GetWedgeValue();
            }
        }
    }
    return;
}
