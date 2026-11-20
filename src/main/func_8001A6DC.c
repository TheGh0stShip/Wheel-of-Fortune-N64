#include "wof.h"

s32 func_8001A6DC(u8 *arg0) {
    s32 i;
    s32 len;
    u8 result;

    result = 32;
    len = func_80009A74(arg0);
    for (i = 0; i < len; i++) {
        if (func_800076E0(arg0[i]) == 0) {
            result = arg0[i];
            break;
        }
    }
    return result;
}
