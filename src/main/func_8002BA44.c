#include "wof.h"

struct n64dk_r12 func_8002BA44(s32 arg1) {
    s32 event;
    s32 tens;
    s32 ones;
    struct n64dk_r12 sp20;
    s8 pad0;

    sp20.w[1] = 1;
    sp20.w[0] = 0;
    while ((event = func_8000ACE8(arg1)) != 0) {
        switch (event) {
        case 33:
            D_8005B2C0[0].unk_20 = D_8005B118[0];
            D_8005B2C0[0].width = D_8005B178[0];
            D_8005B2C0[1].unk_20 = D_8005B118[0];
            D_8005B2C0[1].width = D_8005B178[0];
            func_8000AAB0(arg1, 31, 0);
            sp20.w[0] = 30 / D_800B96B4;
            return sp20;
        case 31:
            sp20.w[1] = 0;
            sp20.w[0] = 1;
            return sp20;
        }
    }
    tens = D_800B40C0 / 10;
    ones = D_800B40C0 % 10;
    D_8005B2C0[0].unk_20 = D_8005B118[tens];
    D_8005B2C0[0].width = D_8005B178[tens];
    D_8005B2C0[1].unk_20 = D_8005B118[ones];
    D_8005B2C0[1].width = D_8005B178[ones];
    return sp20;
}
