#include "wof.h"

void func_80009FD8(void) {
    s32 i;

    for (i = 0; i < 70; i++) {
        D_800B82A0[i].unk_00 = 0;
        D_800B82A0[i].unk_04 = i;
    }
    D_800BEE50 = 0;
    D_800B82A0[0].unk_00 = 0;
    D_800B82E0 = 0;
    D_800B61A4 = 0;
    for (i = 0; i < 70; i++) {
        D_800BA5E0[i] = 0;
    }
}
