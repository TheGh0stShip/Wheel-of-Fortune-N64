#include "wof.h"

extern s32 D_800AFE38;

void func_80006828(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp20[6];
    s32 sp38[2];

    while (func_8003E2A8() == 1) {
    }
    func_8003CCC8(arg1, arg2);
    func_8003CC18(arg1, arg2);
    func_80045628(sp20, 0, 0, arg0, arg1, arg2, &D_800AFE38);
    func_8003E318(&D_800AFE38, sp38, 1);
}
