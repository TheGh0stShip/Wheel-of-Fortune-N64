#include "wof.h"

struct gd_4_s32 { u8 pad[0x4]; s32 v; };
struct gd_30_s32 { u8 pad[0x30]; s32 v; };
extern s32 D_800B96B4;

struct n64dk_r12 func_800345E8(s32 arg1) {
    struct n64dk_r12 sp20;
    s32 sp30;
    s32 sp34;
    s32 sp38;

    sp38 = *(s32 *)((struct gd_30_s32 *)arg1)->v;
    for (;;) {
        sp30 = func_8000ACE8(arg1);
        if (sp30 == 0) {
            break;
        }
        switch (sp30) {
        case 8:
            ((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v = 10;
            break;
        }
    }
    ((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v--;
    if (((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v < 0) {
        if (((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v < -40) {
            sp20.w[1] = 0;
            sp20.w[0] = 1;
            return sp20;
        }
        if (((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v >= -9) {
            func_800343F8(80, 150, 60, 80, 30, 10, 2, 1);
        } else {
            func_800343F8(80, 150, 60, 80, 30, 10, 2, 1);
            sp20.w[1] = 1;
            sp20.w[0] = ((func_8003CE58() % -1) * ((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v) / D_800B96B4;
            return sp20;
        }
    } else {
        sp34 = 0;
        for (;;) {
            if (sp34 >= 4) {
                break;
            }
            func_800343F8(52, 15, 27, 15, 300, 150, 6, 3);
            sp34++;
        }
    }
    sp20.w[1] = 1;
    sp20.w[0] = (func_8003CE58() % 10) / D_800B96B4;
    return sp20;
}
