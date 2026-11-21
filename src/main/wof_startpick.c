// wof_startpick.c -- starting the machine's letter pick and the solve
//
// StartCpuLetterPick ends off an 8-byte boundary with StartSolvePuzzle right after, which happens only
// inside an object. Whether StartLetterPick before it and StartStatus after it are this object's the
// text does not say.

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

/*
=====================
StartSolvePuzzle

StartSolve, the cursor proc and SolvePuzzleProc.
=====================
*/
void StartSolvePuzzle(void) {
    proc_t *task;

    StartSolve();
    CreatProc(CursorProc, 0x1020000);
    task = CreatProc(SolvePuzzleProc, 0x5020000);
    task->data->cursor.index = 6;
}
