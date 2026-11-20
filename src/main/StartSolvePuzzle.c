#include "wof.h"

void StartSolvePuzzle(void) {
    proc_t *task;

    StartSolve();
    CreatProc(CursorProc, 0x1020000);
    task = CreatProc(SolvePuzzleProc, 0x5020000);
    task->data->cursor.index = 6;
}
