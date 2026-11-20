#include "wof.h"

void func_8000B9FC(s32 arg0) {
    if ((u32)D_800BCA04 > (u32)arg0) {
        D_800BCA04 -= arg0;
    } else {
        D_800BCA04 = 0;
    }
    D_800B8290 = D_800BEDB0[D_800BCA04];
    D_800B9984 = D_800BCA18 - D_800B8290;
}
