#include "wof.h"


struct n64dk_r12 func_80021744(s32 arg1) {
    s32 event;
    struct n64dk_r12 result;
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    result.w[1] = 1;
    result.w[0] = 0;
    while ((event = func_8000ACE8(arg1)) != 0) {
        switch (event) {
        case 8:
            if (((data80021744_t *)((proc_t *)arg1)->unk_30)->unk_24 > 0) {
                D_800B8294 = ((data80021744_t *)((proc_t *)arg1)->unk_30)->unk_24;
            }
            D_800B3CB8 = 8;
            break;
        case 34:
            result.w[1] = 0;
            result.w[0] = 1;
            return result;
        }
    }
    func_800213CC(arg1);
    if (D_800B40C4 != 0) {
        func_80017C00(3, 0);
        D_800B96A4 = 0;
        func_8000B9FC(1);
        D_800B3CB8 = 0;
        result.w[1] = 0;
        result.w[0] = 1;
        func_800325D0(1, ((data80021744_t *)((proc_t *)arg1)->unk_30)->unk_10);
        if (((data80021744_t *)((proc_t *)arg1)->unk_30)->unk_20 != 0) {
            func_8000A850(((data80021744_t *)((proc_t *)arg1)->unk_30)->unk_20);
        }
    }
    return result;
}
