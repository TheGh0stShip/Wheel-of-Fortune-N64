#include "wof.h"

s32 func_8000928C(void) {
    s32 result;
    s32 rem;

    if (D_800B39B8[D_800BEDA8].unk_00 == -10000) {
        rem = D_800BEDF8 % 3;
        if (rem == 1) {
            result = 10000;
        } else {
            result = -1;
        }
    } else {
        result = D_800B39B8[D_800BEDA8].unk_00;
    }
    return result;
}
