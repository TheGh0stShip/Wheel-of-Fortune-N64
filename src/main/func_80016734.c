#include "wof.h"

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[0x4];
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
} State;

extern s32 D_800BA5D8;

struct n64dk_r12 func_80016734(s32 arg1) {
    s32 event;
    struct n64dk_r12 result;
    s32 sp28;

    sp28 = ((State *)((proc_t *)arg1)->unk_30)->unk_00;
    result.w[1] = 1;
    result.w[0] = 0;
    for (;;) {
        event = func_8000ACE8(arg1);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 8:
            D_800BA5D8 = ((State *)((proc_t *)arg1)->unk_30)->unk_08 + ((State *)((proc_t *)arg1)->unk_30)->unk_0C * 36;
            return result;
        }
    }
    ((State *)((proc_t *)arg1)->unk_30)->unk_0C += D_800B96B4;
    if (((State *)((proc_t *)arg1)->unk_30)->unk_0C >= ((State *)((proc_t *)arg1)->unk_30)->unk_10) {
        D_800BA5D8 = (((State *)((proc_t *)arg1)->unk_30)->unk_08 - 36) + ((State *)((proc_t *)arg1)->unk_30)->unk_10 * 36;
        func_8000A850(45);
        result.w[1] = 0;
        result.w[0] = 0;
        return result;
    }
    D_800BA5D8 = ((State *)((proc_t *)arg1)->unk_30)->unk_08 + ((State *)((proc_t *)arg1)->unk_30)->unk_0C * 36;
    return result;
}
