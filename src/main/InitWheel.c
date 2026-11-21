#include "wof.h"

/*
=====================
InitWheel

Sets the 24 wedges of the wheel for the round.
=====================
*/
void InitWheel(void) {
    s32 i;
    s32 value;

    curWedge = 0;
    i = 0;
    while (i < 24) {
        switch (round) {
        case 0:
            value = D_8004B860[i];
            break;
        case 1:
            value = D_8004B8C0[i];
            break;
        case 2:
            value = D_8004B920[i];
            break;
        default:
            value = D_8004B980[i];
        }
        wedges[i].claimed = 0;
        if (value == -10000) {
            if (D_800B9538 != 0) {
                wedges[i].value = -1;
                StrCopy(wedges[i].name, "BANKRUPT");
                wedges[i].unk_18 = 0;
                wedges[i].claimed = 1;
            } else {
                wedges[i].value = value;
                StrCopy(wedges[i].name, "10000");
                wedges[i].unk_18 = 1;
            }
        } else if (value < -4) {
            wedges[i].value = value;
            StrCopy(wedges[i].name, "FREE SPIN");
            wedges[i].unk_18 = 1;
        } else if (value == -1) {
            wedges[i].value = -1;
            StrCopy(wedges[i].name, "BANKRUPT");
            wedges[i].unk_18 = 0;
        } else if (value == -2) {
            wedges[i].value = -2;
            StrCopy(wedges[i].name, "LOOSE TURN");
            wedges[i].unk_18 = 0;
        } else if (value == -3) {
            wedges[i].value = -3;
            StrCopy(wedges[i].name, "JACKPOT");
            wedges[i].unk_18 = 1;
        } else {
            wedges[i].value = value;
            IntToStr(wedges[i].name, value);
            wedges[i].unk_18 = 0;
        }
        i++;
    }
}
