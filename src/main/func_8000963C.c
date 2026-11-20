#include "wof.h"

s32 func_80007EEC(s32 arg0);
extern s32 D_800B619C;
extern s32 D_800B96A0;
extern s32 D_800B9980;
extern s32 D_800B9CF8;
extern s32 D_800B9CFC;
extern s32 D_800B9D00;
extern s32 D_800FB808;

void func_8000963C(s32 arg0) {
    D_800B9980 = 0;
    D_800B96A0 = 0;
    if (arg0 == 0) {
        if (func_80007EEC(0) == 2) {
            D_800B9CF8 = 0;
        } else {
            D_800B9CF8 = 1;
        }
        D_800B9CFC = 1;
        D_800B9D00 = 1;
        D_800FB808++;
        if (D_800FB808 >= 3) {
            D_800FB808 = 0;
        }
        return;
    }
    D_800FB808 = D_800B619C % 3;
}
