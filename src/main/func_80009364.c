#include "wof.h"

void func_80009364(s32 arg0) {
    if (arg0 != 0) {
        D_800B953C = func_8000928C();
    } else {
        if (func_8000928C() == -1) {
            D_800B9990[D_800FB808].unk_000 = 0;
            D_800B9990[D_800FB808].unk_0F8 = 0;
            D_800B9990[D_800FB808].unk_00C = 0;
        }
        if (D_800B619C == 2) {
            if (func_8000928C() > 0) {
                D_800B9540 += func_8000928C();
            }
        }
    }
    return;
}
