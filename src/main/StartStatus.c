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
    func_8002EDC0();
    task = CreatProc(StatusProc, 0x5000000);
    MakeScreenObj(task, 0, func_800278F0, 0x5000000);
    D_800BCA14 = 0;
    D_800B9974 = 0;
}
