#include "wof.h"


void func_8002A8C8(s32 arg0, s32 arg1) {
    D_800BED88++;
    func_80002CE0(43);
    if (arg1 != 0) {
        ((proc_t *)arg0)->unk_30->cursor.index--;
        if (((proc_t *)arg0)->unk_30->cursor.index == 12) {
            ((proc_t *)arg0)->unk_30->cursor.index = 25;
        }
        if (((proc_t *)arg0)->unk_30->cursor.index < 0) {
            ((proc_t *)arg0)->unk_30->cursor.index = 12;
        }
        D_8005A998[((proc_t *)arg0)->unk_30->cursor.index].unk_1C = D_8005A998[((proc_t *)arg0)->unk_30->cursor.index].unk_14;
    } else {
        if (((proc_t *)arg0)->unk_30->cursor.index != 3) {
            ((proc_t *)arg0)->unk_30->cursor.index--;
        }
        if (((proc_t *)arg0)->unk_30->cursor.index < 0) {
            ((proc_t *)arg0)->unk_30->cursor.index = 2;
        }
        D_8005A828[((proc_t *)arg0)->unk_30->cursor.index].unk_1C = D_8005A828[((proc_t *)arg0)->unk_30->cursor.index].unk_14;
    }
    D_800B61B5 = ((proc_t *)arg0)->unk_30->cursor.index + 65;
    ((proc_t *)arg0)->unk_30->cursor.unk_0C = 15;
}
