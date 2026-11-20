#include "wof.h"

extern s32 D_800AD950;
extern s32 D_800B3970;
extern s32 D_800B61A0;
extern s32 D_800B8294;
extern s32 D_800B9688;
extern s32 D_800B96AC;
extern u8 D_800B96C4;
extern s32 D_800B9D04;
extern s32 D_800BCA20;
extern s32 D_800BEDE4;
extern s32 D_800FB80C;
extern u64 D_800FB810;

void func_800065D4(s32 arg0) {
    s16 *msg;

    msg = 0;
    D_800B61A0 = 0;
    D_800BEDE4 = 0;
    D_800FB80C = 0;
    func_800068F0();
    func_800447D8(&D_800AD950);
    while (1) {
        func_8003E318(&D_800B9688, &msg, 1);
        switch (*msg) {
        case 1:
            D_800B96AC++;
            D_800FB810++;
            if (D_800B96C4 != 0 && D_800FB80C == 0) {
                D_800FB80C = 1;
                func_8000BB10();
                func_800481F8(&D_800B3970);
            } else if (D_800B96C4 == 0) {
                D_800B9D04 = 0;
            }
            break;
        case 2:
            D_800BEDE4--;
            if (D_800B8294 != 0) {
                D_800BCA20 = func_80002CE0(D_800B8294);
                D_800B8294 = 0;
            }
            break;
        case 4:
            D_800BEDE4 += 2;
            func_80005258();
            break;
        }
    }
}
