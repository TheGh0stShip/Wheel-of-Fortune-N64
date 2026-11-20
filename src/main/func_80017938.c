#include "wof.h"

struct n64dk_r12 func_80017938(proc_t *proc) {
    struct n64dk_r12 sp10;
    s32 unused;  /* NOTE: unused in the original */
    obj_t *cam;

    sp10.w[1] = 1;
    sp10.w[0] = 0;
    if (proc->unk_30->data80017938.unk_04 != D_800FB808) {
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
    cam = func_8000B5DC(0x3000000, 0xFF000000);
    cam->unk_28 = D_80057F50[1].unk_0C + D_800B39A0[D_800FB808][0];
    cam->unk_2C = D_80057F50[1].unk_10 + D_800B39A0[D_800FB808][1];
    return sp10;
}
