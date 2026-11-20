#include "wof.h"

void func_80011F58(void) {
    s32 i;

    for (i = 0; i < 12; i++) {
        if (D_800B9559[0][i] == '+') {
            D_800B9D08[i].unk_04 = D_010A3388;
            D_800B9D08[i].unk_18 = 0x88888888;
            D_800B9D08[i].unk_0C = 0;
        }
    }
    i = 0;
    while (i < 14) {
        if (D_800B9559[1][i] == '+') {
            D_800B9E58[i].unk_04 = D_010A3388;
            D_800B9E58[i].unk_18 = 0x88888888;
            D_800B9E58[i].unk_0C = 0;
        }
        i++;
    }
    i = 0;
    while (i < 14) {
        if (D_800B9559[2][i] == '+') {
            D_800B9FE0[i].unk_04 = D_010A3388;
            D_800B9FE0[i].unk_18 = 0x88888888;
            D_800B9FE0[i].unk_0C = 0;
        }
        i++;
    }
    i = 0;
    while (i < 12) {
        if (D_800B9559[3][i] == '+') {
            D_800BA168[i].unk_04 = D_010A3388;
            D_800BA168[i].unk_18 = 0x88888888;
            D_800BA168[i].unk_0C = 0;
        }
        i++;
    }
}
