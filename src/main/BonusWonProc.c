#include "wof.h"


struct procResult_s BonusWonProc(proc_t *proc) {
    s32 event;
    struct procResult_s sp18;
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    sp18.w[1] = 1;
    sp18.w[0] = 0;
    while ((event = ProcGetMessage(proc)) != 0) {
        switch (event) {
        case 8:
            applause = applause + 6;
            SetVannaAnim(1);
            StartBoardLights();
            StartCelebration();
            KillProcClass(0x5050200, -1, 1);
            players[curPlayer].total = players[curPlayer].total + 0x61A8;
            PlaySound(5);
            MakeScreenObj(proc, 0, func_8002842C, 0x5050000);
            sp18.w[0] = 320 / frameRetraces;
            return sp18;
        }
    }
    SetCameraView(20);
    CreatProc(ShowWinTotalProc, 0x6000000);
    sp18.w[1] = 0;
    sp18.w[0] = 1;
    return sp18;
}
