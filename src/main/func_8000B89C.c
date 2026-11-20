#include "wof.h"

extern s32 D_800B8290;
extern s32 D_800B9984;

void func_8000B89C(s32 arg0) {
    s32 rem;

    rem = D_800B8290 & (arg0 - 1);
    if (rem != 0) {
        D_800B8290 = D_800B8290 + (arg0 - rem);
        D_800B9984 = D_800B9984 - (arg0 - rem);
    }
}
