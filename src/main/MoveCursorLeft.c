// MoveCursorLeft.c -- moves a cursor left over the letters or the choices

#include "wof.h"


/*
=====================
MoveCursorLeft

Moves a cursor left over the letters or the choices.
=====================
*/
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
        letterImages[proc->data->cursor.index].flashLeft = letterImages[proc->data->cursor.index].flashFrames;
    } else {
        if (proc->data->cursor.index != 3) {
            proc->data->cursor.index--;
        }
        if (proc->data->cursor.index < 0) {
            proc->data->cursor.index = 2;
        }
        actionImages[proc->data->cursor.index].flashLeft = actionImages[proc->data->cursor.index].flashFrames;
    }
    curLetter = proc->data->cursor.index + 65;
    proc->data->cursor.delay = 15;
}
