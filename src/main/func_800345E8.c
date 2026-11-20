#include "wof.h"


struct n64dk_r12 func_800345E8(proc_t *proc) {
    struct n64dk_r12 sp20;
    s32 sp30;
    s32 sp34;
    s32 sp38;

    sp38 = proc->unk_30->obj;
    for (;;) {
        sp30 = func_8000ACE8(proc);
        if (sp30 == 0) {
            break;
        }
        switch (sp30) {
        case 8:
            proc->unk_30->data800345E8.unk_04 = 10;
            break;
        }
    }
    proc->unk_30->data800345E8.unk_04--;
    if (proc->unk_30->data800345E8.unk_04 < 0) {
        if (proc->unk_30->data800345E8.unk_04 < -40) {
            sp20.w[1] = 0;
            sp20.w[0] = 1;
            return sp20;
        }
        if (proc->unk_30->data800345E8.unk_04 >= -9) {
            func_800343F8(80, 150, 60, 80, 30, 10, 2, 1);
        } else {
            func_800343F8(80, 150, 60, 80, 30, 10, 2, 1);
            sp20.w[1] = 1;
            sp20.w[0] = ((guRandom() % -1) * proc->unk_30->data800345E8.unk_04) / D_800B96B4;
            return sp20;
        }
    } else {
        sp34 = 0;
        for (;;) {
            if (sp34 >= 4) {
                break;
            }
            func_800343F8(52, 15, 27, 15, 300, 150, 6, 3);
            sp34++;
        }
    }
    sp20.w[1] = 1;
    sp20.w[0] = (guRandom() % 10) / D_800B96B4;
    return sp20;
}
