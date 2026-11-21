// MoveCursorRight.c -- moves a cursor right over the letters or the choices

#include "wof.h"


/*
=====================
MoveCursorRight

Moves a cursor right over the letters or the choices.
=====================
*/
void MoveCursorRight(proc_t *proc, s32 letters, s32 sound) {
    inputCount++;
    if (sound != 0) {
        PlaySound(43);
    }
    if (letters != 0) {
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
