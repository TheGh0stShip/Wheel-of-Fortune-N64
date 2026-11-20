#include "wof.h"

extern s32 D_800B8290;
extern s32 D_800BCA04;
extern s32 D_800BEDB0[];

s32 func_8000B978(void) {
    if ((u32)D_800BCA04 < 10) {
        D_800BEDB0[D_800BCA04++] = D_800B8290;
        return 1;
    } else {
        return 0;
    }
}
