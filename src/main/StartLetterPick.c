// StartLetterPick.c -- letterPickProc for a person

#include "wof.h"

/*
=====================
StartLetterPick

LetterPickProc for a person.
=====================
*/
void StartLetterPick(void) {
    proc_t *task;

    task = CreatProc(LetterPickProc, 0x5010000);
    task->data->cursor.index = 6;
}
