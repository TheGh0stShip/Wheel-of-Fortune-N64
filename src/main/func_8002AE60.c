#include "wof.h"


void func_8002AE60(s32 arg0) {
    s32 i;

    D_800BED88++;
    if (((proc_t *)arg0)->unk_30->cursor.index >= 13) {
        return;
    }
    i = 13;
    while (i < 26) {
        if (D_800B966A[i] != 32) {
            break;
        }
        i++;
    }
    if (i == 26) {
        return;
    }
    func_80002CE0(43);
    ((proc_t *)arg0)->unk_30->cursor.index += 13;
    D_8005A998[((proc_t *)arg0)->unk_30->cursor.index].unk_1C = D_8005A998[((proc_t *)arg0)->unk_30->cursor.index].unk_14;
    D_800B61B5 = ((proc_t *)arg0)->unk_30->cursor.index + 65;
    ((proc_t *)arg0)->unk_30->cursor.unk_0C = 15;
}
