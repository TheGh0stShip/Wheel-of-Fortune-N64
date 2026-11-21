// CheckPercentDone.c -- the share of the puzzle's letters that are turned, from 0 to 1

#include "wof.h"


/*
=====================
CheckPercentDone

The share of the puzzle's letters that are turned, from 0 to 1.
=====================
*/
f32 CheckPercentDone(void) {
    s32 row;
    s32 col;
    f32 count;
    f32 letters;

    count = letters = 0.0f;
    row = 0;
    for (;;) {
        if (row >= 4) {
            break;
        }
        col = 0;
        for (;;) {
            if (col >= 14) {
                break;
            }
            if (board[row][col] == 43) {
                count++;
            }
            if ((u32)puzzleText[row][col] >= 65) {
                if ((u32)puzzleText[row][col] < 91) {
                    letters++;
                }
            }
            col++;
        }
        row++;
    }
    count = letters - count;
    if (letters == 0.0f) {
        func_80009F38("CheckPercentDone: No letters in puzzle\n");
    }
    return count / letters;
}
