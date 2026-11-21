// StartCpuLetterPick.c -- letterPickProc on the letter the machine chose

#include "wof.h"

/*
=====================
StartCpuLetterPick

LetterPickProc on the letter the machine chose.
=====================
*/
void StartCpuLetterPick(register s32 letter) {
    u8 c;
    proc_t *task;

    c = letter;
    task = CreatProc(LetterPickProc, 0x5010000);
    task->data->cursor.index = c - 65;
}
