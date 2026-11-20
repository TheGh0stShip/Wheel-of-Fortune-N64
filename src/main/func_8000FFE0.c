#include "wof.h"

struct n64dk_r12 func_8000FFE0(s32 arg1) {
    struct n64dk_r12 result;
    obj_t *obj;
    s32 event;
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    obj = ((data8000FFE0_t *)((proc_t *)arg1)->unk_30)->unk_00;
    for (;;) {
        event = func_8000ACE8(arg1);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 8:
            ((data8000FFE0_t *)((proc_t *)arg1)->unk_30)->unk_08 = 0;
            obj->unk_48 = &D_010920D8;
            break;
        case 15:
        case 34:
        case 39:
        case 42:
        case 47:
            obj->unk_48 = &D_01092090;
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        }
    }
    ((data8000FFE0_t *)((proc_t *)arg1)->unk_30)->unk_08 = ((data8000FFE0_t *)((proc_t *)arg1)->unk_30)->unk_08 + D_800B96B4;
    if (((data8000FFE0_t *)((proc_t *)arg1)->unk_30)->unk_08 >= 5) {
        ((data8000FFE0_t *)((proc_t *)arg1)->unk_30)->unk_08 = 0;
        if (obj->unk_48 == &D_01092168) {
            obj->unk_48 = &D_010920D8;
        } else if (obj->unk_48 == &D_01092120) {
            obj->unk_48 = &D_01092168;
        } else if (obj->unk_48 == &D_010920D8) {
            obj->unk_48 = &D_01092120;
        }
    }
    result.w[1] = 3;
    result.w[0] = -1;
    return result;
}
