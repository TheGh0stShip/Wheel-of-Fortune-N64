#include "wof.h"

s32 GetWedgeValue(void) {
    s32 result;
    s32 rem;

    if (wedges[curWedge].unk_00 == -10000) {
        rem = wedgeThird % 3;
        if (rem == 1) {
            result = 10000;
        } else {
            result = -1;
        }
    } else {
        result = wedges[curWedge].unk_00;
    }
    return result;
}
