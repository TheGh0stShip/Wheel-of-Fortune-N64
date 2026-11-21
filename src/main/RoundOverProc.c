#include "wof.h"


/*
=====================
RoundOverProc

The puzzle is solved: the camera, the movie, then the next round or the end of the game.
=====================
*/
struct procResult_s RoundOverProc(proc_t *proc) {
    struct procResult_s result;
    s32 unused;  /* NOTE: unused in the original */
    obj_t *obj;
    s32 event;

    result.w[1] = 1;
    result.w[0] = 0;
    for (;;) {
        event = ProcGetMessage(proc);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 8:
            SetGameView(3, 0);
            SetVannaAnim(1);
            func_80032B10();
            if (round != 2) {
                PlayContestantClip(0, 0, curPlayer);
            }
            result.w[1] = 1;
            result.w[0] = 320 / frameRetraces;
            return result;
        case 45:
            SetGameView(3, 0);
            ResetBoard();
            ProcPostEvent(47);
            if (round == 2) {
                PlayMovie(7, 39, 180, 20);
            } else {
                PlayMovie(6, 39, 180, 20);
            }
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        }
    }
    func_80032858();
    func_80032B10();
    round++;
    if (gameOver == 0 && round < numRounds) {
        SetCameraView(13);
        if (round == 2) {
            shownJackpot = 0;
            jackpot = 5000;
            ShowJackpot();
        }
        obj = FindObj(0x4010000, -1);
        obj->pitch = D_8004B848[round] - D_800581F4;
        obj->pitch = obj->pitch - 360.0f;
        result.w[1] = 2;
        result.w[0] = 45;
        return result;
    } else {
        KillProcClass(0x7010000, -1, 0);
        gameOver = 1;
        round = 6;
        CreatProc(WinnerProc, proc->data->playerProc.player | 0x2000600);
        FindWinner();
        result.w[1] = 0;
        result.w[0] = 0;
        return result;
    }
    return result;
}
