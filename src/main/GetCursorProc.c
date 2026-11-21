// GetCursorProc.c -- finds the cursor proc for SolvePuzzleProc, whose message it prints

#include "wof.h"


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
        func_80009F38("SolvePuzzleProc Proc: cursor proc does not exist\n");
    }
    return result;
}
