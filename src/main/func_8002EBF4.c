#include "wof.h"

void func_8002EBF4(void) {
    proc_t *task;

    func_800087F8();
    CreatProc(func_8001228C, 0x1020000);
    task = CreatProc(func_8002E0C8, 0x5020000);
    task->data->cursor.index = 6;
}
