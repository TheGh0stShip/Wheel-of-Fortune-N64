#include "wof.h"


void func_800132EC(s32 arg0) {
    s32 i;

    for (i = 0; i < 3; i++) {
        D_80057BB0[i].unk_04 = 0;
    }
    D_80057BB0[arg0].unk_04 = 1;
    D_80057BB0[arg0].unk_0C = D_80057BB0[arg0].unk_08;
}
