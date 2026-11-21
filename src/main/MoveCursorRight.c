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
        letterImages[proc->data->cursor.index].flashLeft = letterImages[proc->data->cursor.index].flashFrames;
    } else {
        if (proc->data->cursor.index != 3) {
            proc->data->cursor.index++;
            if (proc->data->cursor.index >= 3) {
                proc->data->cursor.index = 0;
            }
        }
        actionImages[proc->data->cursor.index].flashLeft = actionImages[proc->data->cursor.index].flashFrames;
    }
    curLetter = proc->data->cursor.index + 65;
    proc->data->cursor.delay = 15;
}
