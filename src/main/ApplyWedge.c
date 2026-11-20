#include "wof.h"

void ApplyWedge(s32 final) {
    if (final != 0) {
        finalSpinValue = GetWedgeValue();
    } else {
        if (GetWedgeValue() == -1) {
            players[curPlayer].unk_000 = 0;
            players[curPlayer].unk_0F8 = 0;
            players[curPlayer].unk_00C = 0;
        }
        if (round == 2) {
            if (GetWedgeValue() > 0) {
                jackpot += GetWedgeValue();
            }
        }
    }
    return;
}
