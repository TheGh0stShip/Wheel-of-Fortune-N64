#include "wof.h"

extern u32 D_800B3CB8;
extern s32 D_800B61A0;
extern u32 D_800B96AC;
extern s32 D_800B96B4;
extern s32 D_800B9D04;
extern u32 D_800BEDE4;
extern u8 D_800BEF08[][0x1E480];
void func_800057A8(s32 arg0);
void func_8000A664(void);

void func_8000648C(void) {
    s8 pad0;

    while (D_800BEDE4 < 2 && D_800B9D04 == 0) {
        while (D_800B3CB8 > D_800B96AC) {
        }
        D_800B96B4 = D_800B96AC;
        D_800B96AC = 0;
        if (D_800B96B4 == 0) {
            D_800B96B4 = 1;
        }
        func_8000A664();
        D_800B9D04 = 1;
        func_800057A8((s32)D_800BEF08[D_800B61A0]);
        D_800BEDE4++;
        D_800B61A0 ^= 1;
    }
}
