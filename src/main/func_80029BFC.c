#include "wof.h"


void func_80029BFC(s32 arg0) {
    s32 i;

    for (i = 0; i < 7; i++) {
        D_8005ADD0[arg0][i].unk_10 = 1;
    }
}
