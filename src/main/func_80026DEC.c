#include "wof.h"

void func_80026DEC(void) {
    s32 unused;  /* NOTE: unused in the original */
    proc_t *task;

    task = func_8000A56C(func_80024370, 0x05000000);
    func_80027218(task, 0, func_800223A4, 0x05000000);
    func_800258BC();
}
