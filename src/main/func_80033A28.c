#include "wof.h"

struct n64dk_r12 func_80033A28(s32 arg1) {
    struct n64dk_r12 result;
    s32 event;
    s32 sp24;

    result.w[1] = 1;
    result.w[0] = 0;
    while ((event = func_8000ACE8(arg1)) != 0) {
        switch (event) {
        case 8:
            func_80002CE0(10);
            D_800B96A8 = 2;
            ((data80033A28_t *)((proc_t *)arg1)->unk_30)->unk_04 = 0;
            ((data80033A28_t *)((proc_t *)arg1)->unk_30)->unk_08 = 0;
            break;
        }
    }
    if (((data80033A28_t *)((proc_t *)arg1)->unk_30)->unk_04 > 0) {
        switch (((data80033A28_t *)((proc_t *)arg1)->unk_30)->unk_04) {
        case 1:
            sp24 = func_80002CE0(8);
            break;
        case 2:
            sp24 = func_80002CE0(9);
            break;
        case 3:
            sp24 = func_80002CE0(10);
            break;
        default:
            sp24 = func_80002CE0(guRandom() % 3 + 16);
        }
        if (D_800B96A8 == ((data80033A28_t *)((proc_t *)arg1)->unk_30)->unk_04) {
            D_800B96A8 = 0;
            ((data80033A28_t *)((proc_t *)arg1)->unk_30)->unk_04 = 0;
        }
    }
    if (((data80033A28_t *)((proc_t *)arg1)->unk_30)->unk_04 < D_800B96A8) {
        ((data80033A28_t *)((proc_t *)arg1)->unk_30)->unk_04++;
        result.w[0] = 10 / D_800B96B4;
    }
    return result;
}
