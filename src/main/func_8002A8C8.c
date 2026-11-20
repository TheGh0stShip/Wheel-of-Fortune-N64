#include "wof.h"


void func_8002A8C8(s32 arg0, s32 arg1) {
    D_800BED88++;
    func_80002CE0(43);
    if (arg1 != 0) {
        ((cursor_t *)((proc_t *)arg0)->unk_30)->index--;
        if (((cursor_t *)((proc_t *)arg0)->unk_30)->index == 12) {
            ((cursor_t *)((proc_t *)arg0)->unk_30)->index = 25;
        }
        if (((cursor_t *)((proc_t *)arg0)->unk_30)->index < 0) {
            ((cursor_t *)((proc_t *)arg0)->unk_30)->index = 12;
        }
        D_8005A998[((cursor_t *)((proc_t *)arg0)->unk_30)->index].unk_1C = D_8005A998[((cursor_t *)((proc_t *)arg0)->unk_30)->index].unk_14;
    } else {
        if (((cursor_t *)((proc_t *)arg0)->unk_30)->index != 3) {
            ((cursor_t *)((proc_t *)arg0)->unk_30)->index--;
        }
        if (((cursor_t *)((proc_t *)arg0)->unk_30)->index < 0) {
            ((cursor_t *)((proc_t *)arg0)->unk_30)->index = 2;
        }
        D_8005A828[((cursor_t *)((proc_t *)arg0)->unk_30)->index].unk_1C = D_8005A828[((cursor_t *)((proc_t *)arg0)->unk_30)->index].unk_14;
    }
    D_800B61B5 = ((cursor_t *)((proc_t *)arg0)->unk_30)->index + 65;
    ((cursor_t *)((proc_t *)arg0)->unk_30)->unk_0C = 15;
}
