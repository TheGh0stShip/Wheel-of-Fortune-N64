#include "wof.h"

/*
=====================
InitActionCursor

Puts the cursor of StatusProc on the first action the player can take.
=====================
*/
void InitActionCursor(proc_t *proc) {
    proc->data->cursor.index = 2;
    if (canSpin != 0) {
        proc->data->cursor.index = 0;
        return;
    }
    if (canBuyVowel != 0) {
        proc->data->cursor.index = 1;
    }
}
