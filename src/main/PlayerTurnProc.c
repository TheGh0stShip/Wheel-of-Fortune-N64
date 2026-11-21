// PlayerTurnProc.c -- the turn of a person: makes the procs of its steps; named after the ROM's
// "player proc"

#include "wof.h"
#include "rumble.h"


/*
=====================
PlayerTurnProc

The turn of a person: makes the procs of its steps; named after the ROM's "player proc".
=====================
*/
struct procResult_s PlayerTurnProc(proc_t *proc) {
    s32 event;
    struct procResult_s ret;
    proc_t *task;

    ret.w[1] = 1;
    ret.w[0] = 0;
    if (proc->data->playerProc.player != curPlayer) {
        while ((event = ProcGetMessage(proc)) != 0) {
            switch (event) {
            case 42:
                ret.w[1] = 0;
                ret.w[0] = 0;
                return ret;
            }
        }
        return ret;
    }
    while ((event = ProcGetMessage(proc)) != 0) {
        switch (event) {
        case 38:
            PlaySound(players[curPlayer].freeSpinSound);
            players[curPlayer].freeSpin = 0;
            task = FindProc(0x5000000, -1);
            ProcPostMessage(task, 24, 0);
            /* fallthrough */
        case 3:
        case 9:
        case 10:
        case 31:
            SetGameView(3, 0);
            if (CheckSolved(1) == 1) {
                UnlightPlayers();
                task = FindProc(0x5000000, -1);
                ProcPostMessage(task, 21, 0);
                StartBoardLights();
                applause += 3;
                PlaySound(5);
                task = CreatProc(RoundOverProc, proc->data->playerProc.player | 0x2000500);
                task->data->playerProc.player = proc->data->playerProc.player;
                if (gameOver != 0 || round == numRounds - 1) {
                    ret.w[1] = 0;
                    ret.w[0] = 0;
                } else {
                    ret.w[1] = 2;
                    ret.w[0] = 39;
                }
                return ret;
            }
            if (D_800BEE54 == 0 && GetHiddenKinds() == 2) {
                D_800BEE54 = 1;
                PlaySound(6);
            }
            ret.w[1] = 2;
            ret.w[0] = -1;
            return ret;
        case 8:
            ret.w[1] = 2;
            ret.w[0] = 40;
            return ret;
        case 40:
            InitBoard();
            /* fallthrough */
        case 1:
        case 15:
        case 32:
            if (finalSpin == 1) {
                task = CreatProc(FinalSpinTurnProc, proc->data->playerProc.player | 0x2000400);
                task->data->playerProc.player = proc->data->playerProc.player;
                ret.w[1] = 2;
                ret.w[0] = 31;
                return ret;
            }
            SetGameView(3, 0);
            ret.w[1] = 2;
            ret.w[0] = -1;
            return ret;
        case 12:
            if (guRandom() % 100 < 33) {
                PlaySound(players[curPlayer].unk_100);
            }
            jackpotWon = 0;
            task = CreatProc(SpinProc, proc->data->playerProc.player | 0x2000100);
            task->data->playerProc.player = proc->data->playerProc.player;
            ret.w[1] = 2;
            ret.w[0] = 3;
            return ret;
        case 13:
            PlaySound(players[curPlayer].unk_104);
            jackpotWon = 0;
            task = CreatProc(BuyVowelProc, proc->data->playerProc.player | 0x2000200);
            task->data->playerProc.player = proc->data->playerProc.player;
            ret.w[1] = 2;
            ret.w[0] = 9;
            return ret;
        case 14:
            PlaySound(players[curPlayer].unk_108);
            task = CreatProc(SolveProc, proc->data->playerProc.player | 0x2000300);
            task->data->playerProc.player = proc->data->playerProc.player;
            ret.w[1] = 2;
            ret.w[0] = 10;
            return ret;
        case 37:
            jackpotWon = 0;
            task = FindProc(0x5000000, -1);
            curLetter = '3';
            ProcPostMessage(task, 27, 1);
            func_8002FCD8();
            ret.w[1] = 2;
            ret.w[0] = -1;
            return ret;
        case 48:
            PlaySound(1);
            SetGameView(0, 0);
            NextTurn();
            StartRumble(players[curPlayer].controller, 30, 0.8f);
            ret.w[1] = 2;
            ret.w[0] = -1;
            return ret;
        case 39:
            NextRound();
            if (proc->data->playerProc.player != curPlayer) {
                ret.w[1] = 2;
                ret.w[0] = -1;
            } else {
                ret.w[1] = 1;
                ret.w[0] = 0;
            }
            return ret;
        case 30:
            ret.w[1] = 2;
            ret.w[0] = 32;
            return ret;
        case 42:
            ret.w[1] = 0;
            ret.w[0] = 0;
            return ret;
        case 34:
            ret.w[1] = 0;
            ret.w[0] = 0;
            return ret;
        }
    }
    return ret;
}
