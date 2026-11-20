#include "wof.h"


struct n64dk_r12 func_800345E8(s32 arg1) {
    struct n64dk_r12 sp20;
    s32 sp30;
    s32 sp34;
    s32 sp38;

    sp38 = *(s32 *)((proc_t *)arg1)->unk_30;
    for (;;) {
        sp30 = func_8000ACE8(arg1);
        if (sp30 == 0) {
            break;
        }
        switch (sp30) {
        case 8:
            ((data800345E8_t *)((proc_t *)arg1)->unk_30)->unk_04 = 10;
            break;
        }
    }
    ((data800345E8_t *)((proc_t *)arg1)->unk_30)->unk_04--;
    if (((data800345E8_t *)((proc_t *)arg1)->unk_30)->unk_04 < 0) {
        if (((data800345E8_t *)((proc_t *)arg1)->unk_30)->unk_04 < -40) {
            sp20.w[1] = 0;
            sp20.w[0] = 1;
            return sp20;
        }
        if (((data800345E8_t *)((proc_t *)arg1)->unk_30)->unk_04 >= -9) {
            func_800343F8(80, 150, 60, 80, 30, 10, 2, 1);
        } else {
            func_800343F8(80, 150, 60, 80, 30, 10, 2, 1);
            sp20.w[1] = 1;
            sp20.w[0] = ((guRandom() % -1) * ((data800345E8_t *)((proc_t *)arg1)->unk_30)->unk_04) / D_800B96B4;
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
