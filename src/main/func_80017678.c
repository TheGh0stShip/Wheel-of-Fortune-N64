#include "wof.h"

void func_80017678(void) {
    proc_t *handle;

    func_8000963C(0);
    func_800132EC(D_800FB808);
    handle = FindProc(D_800FB808 | 0x2000000, 0xFF0000FF);
    ProcPostMessage(handle, 1, 0);
    handle = FindProc(0x5000000, -1);
    ProcPostMessage(handle, 1, 0);
    return;
}
