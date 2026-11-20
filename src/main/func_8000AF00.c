#include "wof.h"

void func_8000AF00(void) {
    s32 i;

    for (i = 0; i < 100; i++) {
        D_800B40C8[i].unk_0C = 0;
        D_800B40C8[i].index = i;
        D_800B40C8[i].unk_04 = 0;
    }
    D_800BCA10 = 0;
    D_800B40D4 = 0;
    D_800B4118 = 0;
}
