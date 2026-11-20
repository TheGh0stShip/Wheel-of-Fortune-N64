#include "wof.h"

struct n64dk_r12 func_8002B730(s32 arg1) {
    s32 event;
    struct n64dk_r12 ret;
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    ret.w[1] = 1;
    ret.w[0] = 0;
    while ((event = func_8000ACE8(arg1)) != 0) {
        switch (event) {
        case 8:
            D_800BCD54 = 8;
            func_8002A538();
            func_80027218(arg1, 0, (s32)&func_80027F3C, 0x5050100);
            D_800B96A8++;
            ret.w[0] = 30 / D_800B96B4;
            return ret;
        case 46:
            func_8000A56C((s32)&func_8002B318, 0x6060000);
            ret.w[1] = 0;
            ret.w[0] = 0;
            return ret;
        }
    }
    func_80021B04(0, 46);
    ret.w[1] = 2;
    ret.w[0] = 46;
    return ret;
}
