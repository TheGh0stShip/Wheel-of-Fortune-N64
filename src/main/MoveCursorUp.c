#include "wof.h"


void MoveCursorUp(proc_t *proc) {
    s32 i;

    D_800BED88++;
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
    D_8005A998[proc->data->cursor.index].unk_1C = D_8005A998[proc->data->cursor.index].unk_14;
    curLetter = proc->data->cursor.index + 65;
    proc->data->cursor.unk_0C = 15;
}
