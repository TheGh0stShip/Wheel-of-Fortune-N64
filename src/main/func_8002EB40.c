#include "wof.h"

void func_8002EB40(void) {
    proc_t *task;

    task = CreatProc(func_8002D930, 0x5010000);
    task->data->cursor.index = 6;
}
