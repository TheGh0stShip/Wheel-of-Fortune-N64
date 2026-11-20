#include "wof.h"

void func_80006828(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp20[6];
    s32 sp38[2];

    while (osPiGetStatus() == 1) {
    }
    osInvalICache(arg1, arg2);
    osInvalDCache(arg1, arg2);
    osPiStartDma(sp20, 0, 0, arg0, arg1, arg2, &D_800AFE38);
    osRecvMesg(&D_800AFE38, sp38, 1);
}
