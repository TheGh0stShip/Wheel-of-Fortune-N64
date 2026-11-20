#include "wof.h"

struct gd_4_s32 { u8 pad[0x4]; s32 v; };

struct n64dk_r12 func_8002F94C(s32 arg1) {
    struct n64dk_r12 sp10;
    s32 pad0[2];
    s32 sp28;
    s32 sp2C;

    sp10.w[1] = 1;
    sp10.w[0] = 0;
    for (;;) {
        sp28 = func_8000ACE8(arg1);
        if (sp28 == 0) {
            break;
        }
        switch (sp28) {
        case 8:
            ((struct gd_4_s32 *)((proc_t *)arg1)->unk_30)->v = (s32)(osGetTime() / D_80084218);
            break;
        }
    }
    ((struct gd_4_s32 *)((proc_t *)arg1)->unk_30)->v = ((struct gd_4_s32 *)((proc_t *)arg1)->unk_30)->v + D_800BCA1C;
    sp2C = (s32)(osGetTime() / D_80084218);
    if (D_800BCD54 == 4) {
        D_800B40C0 = 20 - (sp2C - ((struct gd_4_s32 *)((proc_t *)arg1)->unk_30)->v);
        if ((sp2C - ((struct gd_4_s32 *)((proc_t *)arg1)->unk_30)->v) >= 20) {
            D_800B40C0 = 0;
            func_8000ABB8(33, 0, 0, 0);
            sp10.w[1] = 0;
        }
    } else {
        if ((sp2C - ((struct gd_4_s32 *)((proc_t *)arg1)->unk_30)->v) >= 8) {
            func_8000ABB8(33, 0, 0, 0);
            func_8000A850(33);
            sp10.w[1] = 0;
        }
    }
    return sp10;
}
