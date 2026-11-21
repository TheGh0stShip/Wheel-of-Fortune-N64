// JackpotRollProc.c -- rolls the old jackpot off and the new one on

#include "wof.h"


/*
=====================
JackpotRollProc

Rolls the old jackpot off and the new one on.
=====================
*/
struct procResult_s JackpotRollProc(proc_t *proc) {
    s32 event;
    s32 i;
    s32 count;
    struct procResult_s sp20;
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    sp20.w[1] = 1;
    sp20.w[0] = 3 / frameRetraces - 1;
    while ((event = ProcGetMessage(proc)) != 0) {
        switch (event) {
        case 8:
            proc->data->jackpotRoll.step = 0;
        }
    }
    proc->data->jackpotRoll.step = proc->data->jackpotRoll.step + 1;
    count = proc->data->jackpotRoll.step;
    if (count >= 17) {
        for (i = 0; i < 9; i++) {
            rollingNumberImages[i].texture = 0;
        }
        sp20.w[1] = 0;
        sp20.w[0] = 0;
        return sp20;
    }
    i = 0;
    while (i < 9) {
        if (rollingNumberImages[i].texture != 0) {
            rollingNumberImages[i].texture = rollingNumberImages[i].texture + rollingNumberImages[i].width;
            rollingNumberImages[i].height = 15 - count;
            if (rollingNumberImages[i].height <= 0) {
                rollingNumberImages[i].texture = 0;
            }
        }
        bigNumberImages[i].y = 61 - count;
        bigNumberImages[i].height = count;
        if (count >= 16) {
            bigNumberImages[i].height = 15;
        }
        i++;
    }
    return sp20;
}
