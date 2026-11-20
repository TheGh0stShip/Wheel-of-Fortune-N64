#include "wof.h"


void func_8002ACE8(s32 arg0) {
    s32 i;

    D_800BED88++;
    if (((proc_t *)arg0)->unk_30->cursor.index < 13) {
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
    ((proc_t *)arg0)->unk_30->cursor.index = ((proc_t *)arg0)->unk_30->cursor.index - 13;
    D_8005A998[((proc_t *)arg0)->unk_30->cursor.index].unk_1C = D_8005A998[((proc_t *)arg0)->unk_30->cursor.index].unk_14;
    D_800B61B5 = ((proc_t *)arg0)->unk_30->cursor.index + 65;
    ((proc_t *)arg0)->unk_30->cursor.unk_0C = 15;
}
