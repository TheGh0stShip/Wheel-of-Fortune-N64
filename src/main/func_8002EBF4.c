#include "wof.h"

void func_8002EBF4(void) {
    proc_t *task;

    func_800087F8();
    func_8000A56C(func_8001228C, 0x1020000);
    task = func_8000A56C(func_8002E0C8, 0x5020000);
    task->unk_30->cursor.index = 6;
}
