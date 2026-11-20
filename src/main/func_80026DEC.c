#include "wof.h"

void func_80026DEC(void) {
    s32 unused;  /* NOTE: unused in the original */
    s32 task;

    task = func_8000A56C((s32)func_80024370, 0x05000000);
    func_80027218(task, 0, (s32)func_800223A4, 0x05000000);
    func_800258BC();
}
