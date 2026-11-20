#include "wof.h"

struct n64dk_r12 func_80017938(s32 arg1) {
    struct n64dk_r12 sp10;
    s32 pad0;
    obj_t *cam;

    sp10.w[1] = 1;
    sp10.w[0] = 0;
    if (((data80017938_t *)((proc_t *)arg1)->unk_30)->unk_04 != D_800FB808) {
        return sp10;
    }
    if ((D_800B9954.button & 1 & 0xFFFF) != 0) {
        D_800B39A0[D_800FB808][1] = D_800B39A0[D_800FB808][1] - 0.5;
    }
    if ((D_800B9954.button & 2 & 0xFFFF) != 0) {
        D_800B39A0[D_800FB808][1] = D_800B39A0[D_800FB808][1] + 0.5;
    }
    if ((D_800B9954.button & 4 & 0xFFFF) != 0) {
        D_800B39A0[D_800FB808][0] = D_800B39A0[D_800FB808][0] - 0.5;
    }
    if ((D_800B9954.button & 8 & 0xFFFF) != 0) {
        D_800B39A0[D_800FB808][0] = D_800B39A0[D_800FB808][0] + 0.5;
    }
    cam = (obj_t *)func_8000B5DC(0x3000000, 0xFF000000);
    cam->unk_28 = D_80057F50[1].unk_0C + D_800B39A0[D_800FB808][0];
    cam->unk_2C = D_80057F50[1].unk_10 + D_800B39A0[D_800FB808][1];
    return sp10;
}
