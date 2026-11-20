#include "wof.h"

extern s32 D_800BA5D8;

void func_800174DC(void) {
    s32 task;
    s32 pad0;
    s8 pad1;

    D_800BA5D8 = 0;
    task = func_8000A56C((s32)&func_80016BEC, 0x3000000);
    if (task == 0) {
        return;
    }
    func_8001745C(task);
}
