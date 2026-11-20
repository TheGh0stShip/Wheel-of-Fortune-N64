#include "wof.h"


void func_8002AAD0(s32 arg0, s32 arg1, s32 arg2) {
    D_800BED88++;
    if (arg2 != 0) {
        func_80002CE0(43);
    }
    if (arg1 != 0) {
        ((cursor_t *)((proc_t *)arg0)->unk_30)->index++;
        if (((cursor_t *)((proc_t *)arg0)->unk_30)->index == 13) {
            ((cursor_t *)((proc_t *)arg0)->unk_30)->index = 0;
        }
        if (((cursor_t *)((proc_t *)arg0)->unk_30)->index >= 26) {
            ((cursor_t *)((proc_t *)arg0)->unk_30)->index = 13;
        }
        D_8005A998[((cursor_t *)((proc_t *)arg0)->unk_30)->index].unk_1C = D_8005A998[((cursor_t *)((proc_t *)arg0)->unk_30)->index].unk_14;
    } else {
        if (((cursor_t *)((proc_t *)arg0)->unk_30)->index != 3) {
            ((cursor_t *)((proc_t *)arg0)->unk_30)->index++;
            if (((cursor_t *)((proc_t *)arg0)->unk_30)->index >= 3) {
                ((cursor_t *)((proc_t *)arg0)->unk_30)->index = 0;
            }
        }
        D_8005A828[((cursor_t *)((proc_t *)arg0)->unk_30)->index].unk_1C = D_8005A828[((cursor_t *)((proc_t *)arg0)->unk_30)->index].unk_14;
    }
    D_800B61B5 = ((cursor_t *)((proc_t *)arg0)->unk_30)->index + 65;
    ((cursor_t *)((proc_t *)arg0)->unk_30)->unk_0C = 15;
}
