#include "wof.h"

/*
=====================
StartCpuLetterPick

LetterPickProc on the letter the machine chose.
=====================
*/
void StartCpuLetterPick(register s32 letter) {
    u8 sp10;
    proc_t *task;

    sp10 = letter;
    task = CreatProc(LetterPickProc, 0x5010000);
    task->data->cursor.index = sp10 - 65;
}
