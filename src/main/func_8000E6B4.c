#include "wof.h"

void func_8000E6B4(void) {
    proc_t *task;
    obj_t *sp14;

    D_800BCD54 = 1;
    func_80005700();
    sp14 = func_80015848(0, 0, func_800288CC, 0x5030000);
    task = func_8000A56C(func_8000E4B0, 0x8010000);
    task->unk_30->obj = sp14;
}
