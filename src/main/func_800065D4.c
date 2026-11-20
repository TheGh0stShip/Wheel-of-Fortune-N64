#include "wof.h"

void func_800065D4(s32 arg0) {
    s16 *msg;

    msg = 0;
    D_800B61A0 = 0;
    D_800BEDE4 = 0;
    D_800FB80C = 0;
    func_800068F0();
    osStartThread(&D_800AD950);
    while (1) {
        osRecvMesg(&D_800B9688, &msg, 1);
        switch (*msg) {
        case 1:
            D_800B96AC++;
            D_800FB810++;
            if (D_800B96C4 != 0 && D_800FB80C == 0) {
                D_800FB80C = 1;
                func_8000BB10();
                osContStartReadData(&D_800B3970);
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
