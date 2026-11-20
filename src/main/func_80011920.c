#include "wof.h"


void func_80011920(void) {
    s32 i;

    for (i = 0; i < 12; i++) {
        D_800B9D08[i].unk_18 = -1;
        D_800B9D08[i].unk_0C = 0;
    }
    i = 0;
    while (i < 14) {
        D_800B9E58[i].unk_18 = -1;
        D_800B9E58[i].unk_0C = 0;
        i++;
    }
    i = 0;
    while (i < 14) {
        D_800B9FE0[i].unk_18 = -1;
        D_800B9FE0[i].unk_0C = 0;
        i++;
    }
    i = 0;
    while (i < 12) {
        D_800BA168[i].unk_18 = -1;
        D_800BA168[i].unk_0C = 0;
        i++;
    }
}
