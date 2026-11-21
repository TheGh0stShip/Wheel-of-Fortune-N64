// wof_players.c -- a person's turn in the final spin and in a round, and the turn procs of the players
//
// FinalSpinTurnProc, PlayerTurnProc and AddPlayer each end off an 8-byte boundary with the next
// function right after, which happens only inside an object. Whether SolveProc before it and
// InitCpuLetters after it are this object's the text does not say.

#include "wof.h"
#include "rumble.h"

/*
=====================
FinalSpinTurnProc

A person's turn in the final spin: a letter, then the solve.
=====================
*/
struct procResult_s FinalSpinTurnProc(proc_t *proc) {
    struct procResult_s ret;
    proc_t *task;
    s32 unused;  /* NOTE: unused in the original */
    s32 event;

    ret.w[1] = 1;
    ret.w[0] = 0;
    if (proc->data->playerProc.player != curPlayer) {
        ProcClearMessages(proc);
        return ret;
    }
    task = FindProc(0x5000000, -1);
    while ((event = ProcGetMessage(proc)) != 0) {
        switch (event) {
        case 8:
            SetGameView(3, 0);
            StartLetterPick();
            ret.w[1] = 2;
            ret.w[0] = 5;
            break;
        case 5:
            PlaySound(players[curPlayer].letterSounds + (curLetter - 'A'));
            ProcPostMessage(proc, 44, 0);
            ret.w[1] = 1;
            ret.w[0] = 30 / frameRetraces;
            return ret;
        case 44:
            if (CallLetter(curLetter, 2) > 0) {
                ShowLetter(curLetter);
                task = CreatProc(LightLetterProc, 0x1000000);
                task->data->lightLetter.letter = curLetter;
                ret.w[1] = 2;
                ret.w[0] = 6;
            } else {
                PlaySound(1);
                StartRumble(players[curPlayer].controller, 30, 0.8f);
                LoseTurn();
                ProcPostEvent(31);
                ProcPostMessage(task, 31, 0);
                ret.w[1] = 0;
                ret.w[0] = 0;
                return ret;
            }
            break;
        case 6:
            SetScorePictures(0);
            StartSolveTimer();
            task = CreatProc(SolveProc, proc->data->playerProc.player | 0x2000300);
            task->data->playerProc.player = proc->data->playerProc.player;
            ret.w[1] = 2;
            ret.w[0] = 10;
            return ret;
        case 10:
            if (CheckSolve() != 1) {
                LoseTurn();
            }
            ProcPostEvent(31);
            ProcPostMessage(task, 31, 0);
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
            if (vowelsOnlyAnnounced == 0 && GetHiddenKinds() == 2) {
                vowelsOnlyAnnounced = 1;
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

/*
=====================
AddPlayer

The turn proc of a person.
=====================
*/
void AddPlayer(s32 player) {
    proc_t *task;
    s32 unused;   /* NOTE: unused in the original */
    s32 unused2;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    task = CreatProc(PlayerTurnProc, player | 0x2020000);
    task->data->playerProc.player = player;
}

/*
=====================
InitPlayers

A turn proc for each contestant, a person's or the machine's.
=====================
*/
void InitPlayers(void) {
    s32 unused;  /* NOTE: unused in the original */
    s32 unused2;  /* NOTE: unused in the original */
    s32 i;

    InitCpuLetters();
    for (i = 0; i < 3; i++) {
        if (gameMode == 3) {
            AddDemoCpu(i);
        } else if (players[i].controller < 4) {
            AddPlayer(i);
        } else {
            AddCpu(i);
        }
        cameraTurn[i][0] = 0;
        cameraTurn[i][1] = 0;
    }
    if (gameMode == 3) {
        SetGameView(17, 0);
        return;
    }
    SetGameView(3, 0);
}
