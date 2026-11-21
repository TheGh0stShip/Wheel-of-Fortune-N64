// wof_solveblanks.c -- the blank squares of the solve, and the cursor proc of SolvePuzzleProc
//
// CountSolveBlanks ends off an 8-byte boundary with GetCursorProc right after, which happens only inside
// an object. Whether LetterPickProc before it and SolvePuzzleProc after it are this object's the text
// does not say.

#include "wof.h"

/*
=====================
CountSolveBlanks

The squares of solveBoard still blank.
=====================
*/
s32 CountSolveBlanks(void) {
    s32 i;
    s32 j;
    s32 count;

    count = 0;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 14; j++) {
            if (solveBoard[i][j] == 43) {
                count++;
            }
        }
    }
    return count;
}

/*
=====================
GetCursorProc

Finds the cursor proc for SolvePuzzleProc, whose message it prints.
=====================
*/
proc_t *GetCursorProc(void) {
    proc_t *result;

    result = FindProc(0x1020000, -1);
    if (result == 0) {
        FatalError("SolvePuzzleProc Proc: cursor proc does not exist\n");
    }
    return result;
}
