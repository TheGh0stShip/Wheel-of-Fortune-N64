#include "wof.h"

s32 func_800076E0(s32 arg0);
s32 func_80009A74(s32 arg0);
s32 func_8001A6DC(s32 arg0);

s32 func_8001A7A8(s32 arg0) {
    s32 i;
    s32 len;
    u8 c;

    c = ' ';
    len = func_80009A74(arg0);
    for (i = 0; i < len; i++) {
        if (func_800076E0(((u8 *)arg0)[i]) > 0) {
            c = ((u8 *)arg0)[i];
            break;
        }
    }
    if (c == ' ') {
        c = func_8001A6DC(arg0);
    }
    return c;
}
