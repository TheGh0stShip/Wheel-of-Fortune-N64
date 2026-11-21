#include "wof.h"


/*
=====================
StartBonusRound

Sets the bonus round (gameMode 4) for the player with the most money.
=====================
*/
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
        CreatProc(ShowTotalProc, 0x6000000);
        return;
    }
    ResetMotors();
    SetGameView(3, 0);
    StartRound();
    ProcPostMessageClass(42, 0, 0, 1);
    handle = CreatProc(BonusRoundProc, 0x5050000);
    MakeScreenObj(handle, 0, DrawLetterPick, 0x5050000);
    InitBoard();
    InitCpuLetters();
    func_8002EDC0();
}
