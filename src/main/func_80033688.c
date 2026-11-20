#include "wof.h"

extern u64 D_80084218;
extern u16 D_800B96B0;
extern s32 D_800BA2C0;
extern s32 D_800BCA1C;
extern s32 D_800BCD54;
extern s32 D_800BED88;
extern s32 D_800BED98;
extern s32 D_800BEE48;

struct n64dk_r12 func_80033688(s32 arg1) {
    struct n64dk_r12 sp10;
    s32 sp20;
    s32 pad0;
    s32 sp28;

    sp10.w[1] = 1;
    sp10.w[0] = 0;
    for (;;) {
        sp28 = func_8000ACE8(arg1);
        if (sp28 == 0) {
            break;
        }
        switch (sp28) {
        case 8:
            D_800BEE48 = (s32)(func_80044988() / D_80084218);
        }
    }
    D_800BCA1C = 0;
    if (D_800BCD54 == 2) {
        if (D_800BED88 > 0) {
            D_800BEE48 = (s32)(func_80044988() / D_80084218);
            D_800BED88 = 0;
        } else {
            if (((func_80044988() / D_80084218) - D_800BEE48) > 30) {
                func_800335D0();
                return sp10;
            }
        }
    } else {
        if (D_800BCD54 == 8) {
            if (((D_800B96B0 & 0xB000) & 0xFFFF) != 0) {
                sp20 = func_8000A990(0x6060000, -1);
                if (sp20 != 0) {
                    func_8000AAB0(sp20, 46, 1);
                }
            }
            return sp10;
        }
    }
    if (((D_800B96B0 & 0x1000) & 0xFFFF) != 0) {
        if (D_800BCD54 != 6) {
            func_800335D0();
        } else {
            func_8000B6FC(0x5020000, -1);
            D_800BCD54 = D_800BED98;
            func_80002B34();
            D_800BCA1C = ((s32)(func_80044988() / D_80084218)) - D_800BA2C0;
            D_800BEE48 = (s32)(func_80044988() / D_80084218);
        }
    }
    return sp10;
}
