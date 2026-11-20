#include "wof.h"


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
