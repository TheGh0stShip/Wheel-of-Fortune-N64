#include "wof.h"

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
