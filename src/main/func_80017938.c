#include "wof.h"

struct procResult_s func_80017938(proc_t *proc) {
    struct procResult_s sp10;
    s32 unused;  /* NOTE: unused in the original */
    obj_t *cam;

    sp10.w[1] = 1;
    sp10.w[0] = 0;
    if (proc->unk_30->data80017938.unk_04 != D_800FB808) {
        return sp10;
    }
    if ((playerPad.button & 1 & 0xFFFF) != 0) {
        D_800B39A0[D_800FB808][1] = D_800B39A0[D_800FB808][1] - 0.5;
    }
    if ((playerPad.button & 2 & 0xFFFF) != 0) {
        D_800B39A0[D_800FB808][1] = D_800B39A0[D_800FB808][1] + 0.5;
    }
    if ((playerPad.button & 4 & 0xFFFF) != 0) {
        D_800B39A0[D_800FB808][0] = D_800B39A0[D_800FB808][0] - 0.5;
    }
    if ((playerPad.button & 8 & 0xFFFF) != 0) {
        D_800B39A0[D_800FB808][0] = D_800B39A0[D_800FB808][0] + 0.5;
    }
    cam = FindObj(0x3000000, 0xFF000000);
    cam->unk_28 = D_80057F50[1].unk_0C + D_800B39A0[D_800FB808][0];
    cam->unk_2C = D_80057F50[1].unk_10 + D_800B39A0[D_800FB808][1];
    return sp10;
}
