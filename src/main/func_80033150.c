#include "wof.h"

s32 func_80033150(s32 arg0, s32 arg1, s32 arg2) {
    obj_t *obj;
    proc_t *other;
    s32 pad0;
    clip_t *slots;
    s32 pad1[2];
    s32 pad2;
    s32 sp34;

    sp34 = 0x2000000;
    if (D_800B9990[arg2].unk_018 >= 6) {
        func_80009F38("InitContestants: invalid image num");
    }
    slots = D_8005C568[D_800B9990[arg2].unk_018];
    if (slots[arg0].count > 0) {
        obj = (obj_t *)func_8000B5DC(arg2 | 0xA020000, -1);
        if (obj == 0) {
            func_80009F38(D_800019BC);
        }
        other = (proc_t *)func_8000A990(arg2 | 0xA000300, -1);
        if (other != 0) {
            func_8000A4A4((s32)other, 0);
        }
        func_80021C8C(slots[arg0].movie, slots[arg0].unk_20, obj, arg2, arg1);
        return 1;
        return; /* dead, kept for the match */
    }
    return 0;
}
