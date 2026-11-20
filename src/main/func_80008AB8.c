#include "wof.h"

void func_80008AB8(void) {
    s32 i;
    s32 value;

    D_800BEDA8 = 0;
    i = 0;
    while (i < 24) {
        switch (D_800B619C) {
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
        D_800B39B8[i].unk_1C = 0;
        if (value == -10000) {
            if (D_800B9538 != 0) {
                D_800B39B8[i].unk_00 = -1;
                StrCopy(D_800B39B8[i].name, "BANKRUPT");
                D_800B39B8[i].unk_18 = 0;
                D_800B39B8[i].unk_1C = 1;
            } else {
                D_800B39B8[i].unk_00 = value;
                StrCopy(D_800B39B8[i].name, "10000");
                D_800B39B8[i].unk_18 = 1;
            }
        } else if (value < -4) {
            D_800B39B8[i].unk_00 = value;
            StrCopy(D_800B39B8[i].name, "FREE SPIN");
            D_800B39B8[i].unk_18 = 1;
        } else if (value == -1) {
            D_800B39B8[i].unk_00 = -1;
            StrCopy(D_800B39B8[i].name, "BANKRUPT");
            D_800B39B8[i].unk_18 = 0;
        } else if (value == -2) {
            D_800B39B8[i].unk_00 = -2;
            StrCopy(D_800B39B8[i].name, "LOOSE TURN");
            D_800B39B8[i].unk_18 = 0;
        } else if (value == -3) {
            D_800B39B8[i].unk_00 = -3;
            StrCopy(D_800B39B8[i].name, "JACKPOT");
            D_800B39B8[i].unk_18 = 1;
        } else {
            D_800B39B8[i].unk_00 = value;
            IntToStr(D_800B39B8[i].name, value);
            D_800B39B8[i].unk_18 = 0;
        }
        i++;
    }
}
