#include "wof.h"

struct n64dk_r12 func_8000C310(proc_t *proc) {
    struct n64dk_r12 result;
    obj_t *obj;
    s32 event;

    obj = proc->unk_30->data8000C310.unk_00;
    for (;;) {
        event = func_8000ACE8(proc);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 34:
        case 36:
            result.w[1] = 0;
            result.w[0] = 1;
            return result;
        }
    }
    result.w[1] = 1;
    result.w[0] = 0;
    func_8000AD9C(proc);
    result.w[1] = 1;
    result.w[0] = 0;
    obj->unk_2C -= (f32)D_800B96B4;
    if (D_800B3994 >= 601) {
        obj->y = obj->y + D_800B96B4;
    }
    if (obj->y >= 41) {
        obj->y = 40;
    }
    if (D_800B3994 % 2 == 1) {
        if (obj->unk_48 == (s32)D_011358C0) {
            obj->unk_48 = (s32)D_01135908;
        } else {
            obj->unk_48 = (s32)D_011358C0;
        }
    }
    return result;
}
