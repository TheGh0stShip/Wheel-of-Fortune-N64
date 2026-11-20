#include "wof.h"


void StartSolve(void) {
    s32 i;
    s32 j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 14; j++) {
            solveBoard[i][j] = board[i][j];
        }
    }
}
