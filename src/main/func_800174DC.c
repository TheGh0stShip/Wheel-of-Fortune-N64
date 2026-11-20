#include "wof.h"

void func_800174DC(void) {
    proc_t *task;
    s32 unused;  /* NOTE: unused in the original */
    s32 unused2;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    D_800BA5D8 = 0;
    task = func_8000A56C(func_80016BEC, 0x3000000);
    if (task == 0) {
        return;
    }
    func_8001745C(task);
}
