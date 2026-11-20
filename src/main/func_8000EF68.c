#include "wof.h"


struct n64dk_r12 func_8000EF68(s32 arg1) {
    // The locals are func_8000F274's, slot for slot; this handler leaves three of them unused.
    struct n64dk_r12 ret;
    obj_t *unused;  /* NOTE: unused in the original */
    obj_t *obj;
    f32 delta;
    f32 unused2;  /* NOTE: unused in the original */
    s32 unused3;  /* NOTE: unused in the original */
    s32 event;

    ret.w[1] = 1;
    ret.w[0] = 0;
    obj = (obj_t *)func_8000B5DC(0x4010000, 0xFFFF0000);
    if (obj == 0) {
        return ret;
    }
    for (;;) {
        event = func_8000ACE8(arg1);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 8:
            ((data8000EF68_t *)((proc_t *)arg1)->unk_30)->unk_0C = obj->unk_2C;
            break;
        case 34:
            ret.w[1] = 0;
            ret.w[0] = 0;
            return ret;
        }
    }
    delta = ((data8000EF68_t *)((proc_t *)arg1)->unk_30)->unk_0C - D_800B9954.stick_x / D_80057F44;
    if (delta > 0.0f) {
        delta = delta * -1.0f;
    }
    delta = delta - obj->unk_2C;
    delta = delta / (f32)(12 / D_800B96B4);
    D_800BCCF0 = delta * -1.0f * 60.0f;
    obj->unk_2C = obj->unk_2C + delta;
    if ((D_800B96B0 & 0xA000 & 0xFFFF) != 0) {
        D_800BCCF0 = (f32)(guRandom() % 40) + 100.0f;
        func_8000A850(29);
        ret.w[1] = 0;
        ret.w[0] = 0;
    }
    if (D_80057F48 < D_800BCCF0) {
        func_8000A850(29);
        ret.w[1] = 0;
        ret.w[0] = 0;
    }
    return ret;
}
