// InitWheel.c -- sets the 24 wedges of the wheel for the round

#include "wof.h"

s32 firstRoundWedges[24] = {
    -1, 300, 250, 900, 400, 150, 250, 400, 300, -2, 400, 500, 200, 700, 500, 200, 300, 400, 500,
    1000, 200, 300, 800, 750
};
s32 secondRoundWedges[24] = {
    -1, 300, 250, 900, 400, 800, 250, 400, 550, -2, 400, 500, 350, 700, 500, 200, 300, 400, 500,
    2500, 200, 300, 800, 750
};
s32 jackpotRoundWedges[24] = {
    -1, 900, 3500, 250, 900, -3, 400, 550, -200, 500, -10000, 600, 200, 1000, 600, 300, 700, 450,
    300, 800, -2, 250, 400, 500
};
s32 laterRoundWedges[24] = {
    350, 900, 300, 250, 900, 200, 400, 550, 200, 500, -10000, 600, 200, -2, 350, 250, 500, 5000,
    300, 800, 500, 700, -1, 1500
};

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
            value = firstRoundWedges[i];
            break;
        case 1:
            value = secondRoundWedges[i];
            break;
        case 2:
            value = jackpotRoundWedges[i];
            break;
        default:
            value = laterRoundWedges[i];
        }
        wedges[i].claimed = 0;
        if (value == -10000) {
            if (prizeTaken != 0) {
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
