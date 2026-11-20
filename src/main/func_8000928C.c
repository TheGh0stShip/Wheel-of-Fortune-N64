#include "wof.h"

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[0x1C];
} Entry;

extern Entry D_800B39B8[];

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
