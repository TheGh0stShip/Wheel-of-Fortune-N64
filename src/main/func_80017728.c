#include "wof.h"


s32 func_80017728(void) {
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    if (D_800B9990[D_800FB808].unk_008 != 0 && D_800BCA00 == 0) {
        return 0;
    }
    return 1;
}
