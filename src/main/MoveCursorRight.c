#include "wof.h"


void MoveCursorRight(proc_t *proc, s32 arg1, s32 arg2) {
    inputCount++;
    if (arg2 != 0) {
        PlaySound(43);
    }
    if (arg1 != 0) {
        proc->data->cursor.index++;
        if (proc->data->cursor.index == 13) {
            proc->data->cursor.index = 0;
        }
        if (proc->data->cursor.index >= 26) {
            proc->data->cursor.index = 13;
        }
        letterImages[proc->data->cursor.index].unk_1C = letterImages[proc->data->cursor.index].unk_14;
    } else {
        if (proc->data->cursor.index != 3) {
            proc->data->cursor.index++;
            if (proc->data->cursor.index >= 3) {
                proc->data->cursor.index = 0;
            }
        }
        actionImages[proc->data->cursor.index].unk_1C = actionImages[proc->data->cursor.index].unk_14;
    }
    curLetter = proc->data->cursor.index + 65;
    proc->data->cursor.unk_0C = 15;
}
