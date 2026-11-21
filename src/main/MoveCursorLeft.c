#include "wof.h"


void MoveCursorLeft(proc_t *proc, s32 arg1) {
    inputCount++;
    PlaySound(43);
    if (arg1 != 0) {
        proc->data->cursor.index--;
        if (proc->data->cursor.index == 12) {
            proc->data->cursor.index = 25;
        }
        if (proc->data->cursor.index < 0) {
            proc->data->cursor.index = 12;
        }
        letterImages[proc->data->cursor.index].unk_1C = letterImages[proc->data->cursor.index].unk_14;
    } else {
        if (proc->data->cursor.index != 3) {
            proc->data->cursor.index--;
        }
        if (proc->data->cursor.index < 0) {
            proc->data->cursor.index = 2;
        }
        actionImages[proc->data->cursor.index].unk_1C = actionImages[proc->data->cursor.index].unk_14;
    }
    curLetter = proc->data->cursor.index + 65;
    proc->data->cursor.unk_0C = 15;
}
