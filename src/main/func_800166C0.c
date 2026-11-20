#include "wof.h"

extern s32 D_800BA2BC;

s32 func_800166C0(void) {
    s32 result;

    switch (D_800BA2BC) {
    case 3:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 18:
    case 20:
        result = 0;
        break;
    default:
        result = 1;
    }
    return result;
}
