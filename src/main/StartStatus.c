// StartStatus.c -- statusProc and its obj

#include "wof.h"


/*
=====================
StartStatus

StatusProc and its obj.
=====================
*/
void StartStatus(void) {
    proc_t *task;
    s32 i;
    s32 j;

    for (i = 0; i < 3; i++) {
        playerStatusImages[i][0].flash = 0;
        playerStatusImages[i][1].flash = 0;
        for (j = 0; j < 7; j++) {
            statusScoreImages[i][j].flash = 0;
        }
    }
    StatusStub();
    task = CreatProc(StatusProc, 0x5000000);
    MakeScreenObj(task, 0, DrawStatus, 0x5000000);
    startStatusZero1 = 0;
    startStatusZero2 = 0;
}
