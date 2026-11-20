#include "wof.h"

void StartLetterPick(void) {
    proc_t *task;

    task = CreatProc(LetterPickProc, 0x5010000);
    task->data->cursor.index = 6;
}
