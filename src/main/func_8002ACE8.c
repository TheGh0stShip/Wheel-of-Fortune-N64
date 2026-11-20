#include "wof.h"


void func_8002ACE8(s32 arg0) {
    s32 i;

    D_800BED88++;
    if (((cursor_t *)((proc_t *)arg0)->unk_30)->index < 13) {
        return;
    }
    i = 0;
    for (;;) {
        if (i >= 13) {
            break;
        }
        if (D_800B966A[i] != 32) {
            break;
        }
        i++;
    }
    if (i == 13) {
        return;
    }
    func_80002CE0(43);
    ((cursor_t *)((proc_t *)arg0)->unk_30)->index = ((cursor_t *)((proc_t *)arg0)->unk_30)->index - 13;
    D_8005A998[((cursor_t *)((proc_t *)arg0)->unk_30)->index].unk_1C = D_8005A998[((cursor_t *)((proc_t *)arg0)->unk_30)->index].unk_14;
    D_800B61B5 = ((cursor_t *)((proc_t *)arg0)->unk_30)->index + 65;
    ((cursor_t *)((proc_t *)arg0)->unk_30)->unk_0C = 15;
}
