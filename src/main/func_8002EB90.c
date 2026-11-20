#include "wof.h"

void func_8002EB90(register s32 arg0) {
    u8 sp10;
    proc_t *task;

    sp10 = arg0;
    task = CreatProc(func_8002D930, 0x5010000);
    task->data->cursor.index = sp10 - 65;
}
