#include "wof.h"


void func_80011920(void) {
    s32 i;

    for (i = 0; i < 12; i++) {
        D_800B9D0C[i].unk_14 = -1;
        D_800B9D0C[i].unk_08 = 0;
    }
    i = 0;
    while (i < 14) {
        D_800B9E5C[i].unk_14 = -1;
        D_800B9E5C[i].unk_08 = 0;
        i++;
    }
    i = 0;
    while (i < 14) {
        D_800B9FE4[i].unk_14 = -1;
        D_800B9FE4[i].unk_08 = 0;
        i++;
    }
    i = 0;
    while (i < 12) {
        D_800BA16C[i].unk_14 = -1;
        D_800BA16C[i].unk_08 = 0;
        i++;
    }
}
