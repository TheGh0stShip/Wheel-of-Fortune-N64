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
    letterImages[proc->data->cursor.index].flashLeft = letterImages[proc->data->cursor.index].flashFrames;
    curLetter = proc->data->cursor.index + 65;
    proc->data->cursor.delay = 15;
}
