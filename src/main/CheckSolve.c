// CheckSolve.c -- 1 and the whole puzzle shown if solveBoard is the puzzle

#include "wof.h"


/*
=====================
CheckSolve

1 and the whole puzzle shown if solveBoard is the puzzle.
=====================
*/
s32 CheckSolve(void) {
    s32 i;
    s32 j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 14; j++) {
            if (puzzleText[i][j] != solveBoard[i][j]) {
                return 0;
            }
        }
    }
    i = 0;
    while (i < 4) {
        for (j = 0; j < 14; j++) {
            board[i][j] = puzzleText[i][j];
        }
        i++;
    }
    return 1;
}
