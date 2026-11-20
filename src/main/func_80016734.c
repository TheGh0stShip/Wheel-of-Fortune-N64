#include "wof.h"

struct n64dk_r12 func_80016734(s32 arg1) {
    s32 event;
    struct n64dk_r12 result;
    s32 sp28;

    sp28 = ((data80016734_t *)((proc_t *)arg1)->unk_30)->unk_00;
    result.w[1] = 1;
    result.w[0] = 0;
    for (;;) {
        event = func_8000ACE8(arg1);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 8:
            D_800BA5D8 = &((data80016734_t *)((proc_t *)arg1)->unk_30)->unk_08[((data80016734_t *)((proc_t *)arg1)->unk_30)->unk_0C];
            return result;
        }
    }
    ((data80016734_t *)((proc_t *)arg1)->unk_30)->unk_0C += D_800B96B4;
    if (((data80016734_t *)((proc_t *)arg1)->unk_30)->unk_0C >= ((data80016734_t *)((proc_t *)arg1)->unk_30)->unk_10) {
        D_800BA5D8 = ((data80016734_t *)((proc_t *)arg1)->unk_30)->unk_08 - 1 + ((data80016734_t *)((proc_t *)arg1)->unk_30)->unk_10;
        func_8000A850(45);
        result.w[1] = 0;
        result.w[0] = 0;
        return result;
    }
    D_800BA5D8 = &((data80016734_t *)((proc_t *)arg1)->unk_30)->unk_08[((data80016734_t *)((proc_t *)arg1)->unk_30)->unk_0C];
    return result;
}
