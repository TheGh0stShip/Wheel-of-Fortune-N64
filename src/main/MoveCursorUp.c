#include "wof.h"


void MoveCursorUp(proc_t *proc) {
    s32 i;

    inputCount++;
    if (proc->data->cursor.index < 13) {
        return;
    }
    i = 0;
    for (;;) {
        if (i >= 13) {
            break;
        }
        if (uncalled[i] != 32) {
            break;
        }
        i++;
    }
    if (i == 13) {
        return;
    }
    PlaySound(43);
    proc->data->cursor.index = proc->data->cursor.index - 13;
    letterImages[proc->data->cursor.index].unk_1C = letterImages[proc->data->cursor.index].unk_14;
    curLetter = proc->data->cursor.index + 65;
    proc->data->cursor.delay = 15;
}
