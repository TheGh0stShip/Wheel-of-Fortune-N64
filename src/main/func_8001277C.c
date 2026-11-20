#include "wof.h"

s32 func_8001277C(tile_t *arg0) {
    s32 result;

    result = arg0->unk_18;
    if (arg0->unk_0C != 0) {
        if (arg0->unk_14 > arg0->unk_10 / 2) {
            result = -1;
        }
        arg0->unk_14 = arg0->unk_14 - D_800B96B4;
        if (arg0->unk_14 < 0) {
            arg0->unk_14 = arg0->unk_10;
        }
    }
    return result;
}
