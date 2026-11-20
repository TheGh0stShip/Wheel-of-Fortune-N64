#include "wof.h"


s32 func_80017548(void) {
    proc_t *handle;

    if (D_800B9990[D_800FB808].unk_008 != 0 && D_800BCA00 == 0) {
        ProcPostMessageClass(37, D_800FB808 | 0x2000000, 0xFF0000FF, 1);
        return 0;
    }
    func_8000963C(0);
    func_800132EC(D_800FB808);
    handle = FindProc(D_800FB808 | 0x2000000, 0xFF0000FF);
    ProcPostMessage(handle, 1, 0);
    handle = FindProc(0x5000000, -1);
    ProcPostMessage(handle, 1, 0);
    return 1;
}
