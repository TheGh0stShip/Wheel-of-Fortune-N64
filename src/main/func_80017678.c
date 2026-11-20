#include "wof.h"

extern s32 D_800FB808;
void func_8000963C(s32 arg0);
s32 func_8000A990(s32 arg0, s32 arg1);
void func_8000AAB0(s32 arg0, s32 arg1, s32 arg2);
void func_800132EC(s32 arg0);

void func_80017678(void) {
    s32 handle;

    func_8000963C(0);
    func_800132EC(D_800FB808);
    handle = func_8000A990(D_800FB808 | 0x2000000, 0xFF0000FF);
    func_8000AAB0(handle, 1, 0);
    handle = func_8000A990(0x5000000, -1);
    func_8000AAB0(handle, 1, 0);
    return;
}
