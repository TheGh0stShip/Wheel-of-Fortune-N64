#include "wof.h"


void StartBonusRound(void) {
    proc_t *handle;
    s32 i;

    round = 6;
    gameMode = 4;
    finalSpin = 0;
    curPlayer = 0;
    for (i = 0; i < 3; i++) {
        if (players[i].total > players[curPlayer].total) {
            curPlayer = i;
        }
    }
    if (players[curPlayer].controller == 4) {
        ProcPostMessageClass(42, 0, 0, 1);
        CreatProc(func_8002B094, 0x6000000);
        return;
    }
    ResetMotors();
    SetGameView(3, 0);
    StartRound();
    ProcPostMessageClass(42, 0, 0, 1);
    handle = CreatProc(func_8002C094, 0x5050000);
    func_80027218(handle, 0, func_80028194, 0x5050000);
    InitBoard();
    InitCpuLetters();
    func_8002EDC0();
}
