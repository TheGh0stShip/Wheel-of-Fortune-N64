#include "wof.h"


struct n64dk_r12 func_80029C98(s32 arg1) {
    s32 event;
    s32 i;
    s32 count;
    struct n64dk_r12 sp20;
    s8 pad0;

    sp20.w[1] = 1;
    sp20.w[0] = 3 / D_800B96B4 - 1;
    while ((event = func_8000ACE8(arg1)) != 0) {
        switch (event) {
        case 8:
            ((data80029C98_t *)((proc_t *)arg1)->unk_30)->unk_10 = 0;
        }
    }
    ((data80029C98_t *)((proc_t *)arg1)->unk_30)->unk_10 = ((data80029C98_t *)((proc_t *)arg1)->unk_30)->unk_10 + 1;
    count = ((data80029C98_t *)((proc_t *)arg1)->unk_30)->unk_10;
    if (count >= 17) {
        for (i = 0; i < 9; i++) {
            D_8005B360[i].unk_20 = 0;
        }
        sp20.w[1] = 0;
        sp20.w[0] = 0;
        return sp20;
    }
    i = 0;
    while (i < 9) {
        if (D_8005B360[i].unk_20 != 0) {
            D_8005B360[i].unk_20 = D_8005B360[i].unk_20 + D_8005B360[i].width * 2;
            D_8005B360[i].height = 15 - count;
            if (D_8005B360[i].height <= 0) {
                D_8005B360[i].unk_20 = 0;
            }
        }
        D_8005B4C8[i].y = 61 - count;
        D_8005B4C8[i].height = count;
        if (count >= 16) {
            D_8005B4C8[i].height = 15;
        }
        i++;
    }
    return sp20;
}
