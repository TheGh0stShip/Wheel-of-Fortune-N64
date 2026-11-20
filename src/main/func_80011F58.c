#include "wof.h"

void func_80011F58(void) {
    s32 i;

    for (i = 0; i < 12; i++) {
        if (D_800B9559[0][i] == '+') {
            D_800B9D0C[i].unk_00 = &D_010A3388;
            D_800B9D0C[i].unk_14 = 0x88888888;
            D_800B9D0C[i].unk_08 = 0;
        }
    }
    i = 0;
    while (i < 14) {
        if (D_800B9559[1][i] == '+') {
            D_800B9E5C[i].unk_00 = &D_010A3388;
            D_800B9E5C[i].unk_14 = 0x88888888;
            D_800B9E5C[i].unk_08 = 0;
        }
        i++;
    }
    i = 0;
    while (i < 14) {
        if (D_800B9559[2][i] == '+') {
            D_800B9FE4[i].unk_00 = &D_010A3388;
            D_800B9FE4[i].unk_14 = 0x88888888;
            D_800B9FE4[i].unk_08 = 0;
        }
        i++;
    }
    i = 0;
    while (i < 12) {
        if (D_800B9559[3][i] == '+') {
            D_800BA16C[i].unk_00 = &D_010A3388;
            D_800BA16C[i].unk_14 = 0x88888888;
            D_800BA16C[i].unk_08 = 0;
        }
        i++;
    }
}
