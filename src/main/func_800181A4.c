#include "wof.h"

typedef struct {
    /* 0x000 */ s32 unk_00;
    /* 0x004 */ u8 unk_04[0x110];
} Player;

extern Player D_800B9AA0[];

struct n64dk_r12 func_800181A4(s32 arg1) {
    struct n64dk_r12 ret;
    s32 pad0[2];
    s32 event;

    ret.w[1] = 1;
    ret.w[0] = 0;
    while ((event = func_8000ACE8(arg1)) != 0) {
        switch (event) {
        case 8:
            func_80017C00(17, 0);
            func_80032B10();
            func_800334E4();
            D_800B96A8 += 3;
            if (D_800B9AA0[D_800FB808].unk_00 > 0) {
                func_80002CE0(D_800B9AA0[D_800FB808].unk_00);
            }
            ret.w[1] = 1;
            ret.w[0] = 45 / D_800B96B4;
            return ret;
        }
    }
    if (D_800FB808 == 0) {
        func_800219B8(11, 42, 185, 20);
    } else {
        func_80021B04(11, 42);
    }
    ret.w[1] = 0;
    ret.w[0] = 0;
    return ret;
}
