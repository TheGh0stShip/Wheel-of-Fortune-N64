#include "wof.h"

extern s32 D_80000768;
extern f32 D_80000790;
extern f32 D_80000794;
extern u8 D_800B9559[][21];
extern u8 D_800B9601[][21];

f32 func_80008628(void) {
    s32 sp10;
    s32 sp14;
    f32 sp18;
    f32 sp1C;

    sp18 = sp1C = 0.0f;
    sp10 = 0;
    for (;;) {
        if (sp10 >= 4) {
            break;
        }
        sp14 = 0;
        for (;;) {
            if (sp14 >= 14) {
                break;
            }
            if (D_800B9559[sp10][sp14] == 43) {
                sp18++;
            }
            if ((u32)D_800B9601[sp10][sp14] >= 65) {
                if ((u32)D_800B9601[sp10][sp14] < 91) {
                    sp1C++;
                }
            }
            sp14++;
        }
        sp10++;
    }
    sp18 = sp1C - sp18;
    if (sp1C == 0.0f) {
        func_80009F38(((s32)&D_80000768));
    }
    return sp18 / sp1C;
}
