#include "wof.h"


void InitLetterCursor(proc_t *proc) {
    if (uncalled[proc->data->cursor.index] == 32) {
        MoveCursorRight(proc, 1, 0);
    }
    curLetter = proc->data->cursor.index + 65;
}
