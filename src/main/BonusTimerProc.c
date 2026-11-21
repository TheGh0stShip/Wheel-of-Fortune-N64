// BonusTimerProc.c -- shows the seconds left to solve the bonus puzzle

#include "wof.h"

/*
=====================
BonusTimerProc

Shows the seconds left to solve the bonus puzzle.
=====================
*/
struct procResult_s BonusTimerProc(proc_t *proc) {
    s32 event;
    s32 tens;
    s32 ones;
    struct procResult_s result;
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    result.w[1] = 1;
    result.w[0] = 0;
    while ((event = ProcGetMessage(proc)) != 0) {
        switch (event) {
        case 33:
            bonusTimerImages[0].texture = bigDigitTextures[0];
            bonusTimerImages[0].width = bigDigitWidths[0];
            bonusTimerImages[1].texture = bigDigitTextures[0];
            bonusTimerImages[1].width = bigDigitWidths[0];
            ProcPostMessage(proc, 31, 0);
            result.w[0] = 30 / frameRetraces;
            return result;
        case 31:
            result.w[1] = 0;
            result.w[0] = 1;
            return result;
        }
    }
    tens = bonusTimeLeft / 10;
    ones = bonusTimeLeft % 10;
    bonusTimerImages[0].texture = bigDigitTextures[tens];
    bonusTimerImages[0].width = bigDigitWidths[tens];
    bonusTimerImages[1].texture = bigDigitTextures[ones];
    bonusTimerImages[1].width = bigDigitWidths[ones];
    return result;
}
