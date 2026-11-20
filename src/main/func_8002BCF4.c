#include "wof.h"

struct n64dk_r12 func_8002BCF4(s32 arg1) {
    s32 busy;
    s32 tens;
    s32 ones;
    struct n64dk_r12 result;
    s8 pad0;

    result.w[1] = 1;
    result.w[0] = 0;
    do {
        busy = func_8000ACE8(arg1);
    } while (busy != 0);
    tens = D_800B96B4 / 10;
    ones = D_800B96B4 % 10;
    D_8005B330 = D_8005B118[tens];
    D_8005B318 = D_8005B178[tens];
    D_8005B358 = D_8005B118[ones];
    D_8005B340 = D_8005B178[ones];
    return result;
}
