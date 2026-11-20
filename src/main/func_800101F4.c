#include "wof.h"

typedef struct {
    /* 0x00 */ obj_t *unk_00;
    /* 0x04 */ u8 unk_04[0x4];
    /* 0x08 */ s32 unk_08;
} State;

struct n64dk_r12 func_800101F4(s32 arg1) {
    struct n64dk_r12 result;
    obj_t *obj;
    s32 event;
    s8 pad0;

    obj = ((State *)((proc_t *)arg1)->unk_30)->unk_00;
    for (;;) {
        event = func_8000ACE8(arg1);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 8:
            ((State *)((proc_t *)arg1)->unk_30)->unk_08 = 0;
            obj->unk_48 = &D_011358C0;
            break;
        case 2:
            obj->unk_48 = &D_01135878;
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        }
    }
    ((State *)((proc_t *)arg1)->unk_30)->unk_08 = ((State *)((proc_t *)arg1)->unk_30)->unk_08 + D_800B96B4;
    if (((State *)((proc_t *)arg1)->unk_30)->unk_08 >= 6) {
        ((State *)((proc_t *)arg1)->unk_30)->unk_08 = 0;
        if (obj->unk_48 == &D_011358C0) {
            obj->unk_48 = &D_01135908;
        } else {
            obj->unk_48 = &D_011358C0;
        }
    }
    result.w[1] = 3;
    result.w[0] = -1;
    return result;
}
