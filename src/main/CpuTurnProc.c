#include "wof.h"


struct procResult_s CpuTurnProc(proc_t *proc) {
    s32 event;
    struct procResult_s ret;
    proc_t *task;

    ret.w[1] = 1;
    ret.w[0] = 0;
    if (proc->data->playerProc.player != curPlayer) {
        while ((event = ProcGetMessage(proc)) != 0) {
            switch (event) {
            case 34:
                ret.w[1] = 0;
                ret.w[0] = 0;
                return ret;
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
            PlaySound(players[curPlayer].unk_10C);
            players[curPlayer].freeSpin = 0;
            /* fallthrough */
        case 3:
        case 9:
        case 10:
        case 31:
            SetGameView(3, 1);
            task = FindProc(0x5000000, -1);
            ProcPostMessage(task, 24, 0);
            if (CheckSolved(1) == 1) {
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
            ProcPostMessage(proc, 28, 0);
            ret.w[1] = 1;
            ret.w[0] = 20 / frameRetraces;
            return ret;
        case 8:
            ret.w[1] = 2;
            ret.w[0] = 40;
            return ret;
        case 40:
            InitBoard();
            ProcPostMessage(proc, 1, 0);
            SetGameView(3, 1);
            ret.w[1] = 1;
            ret.w[0] = 60 / frameRetraces;
            return ret;
        case 1:
        case 32:
            ProcPostEvent(24);
            if (finalSpin == 1) {
                task = CreatProc(CpuFinalSpinTurnProc, proc->data->playerProc.player | 0x2030400);
                task->data->playerProc.player = proc->data->playerProc.player;
                task->data->playerProc.skill = proc->data->playerProc.skill;
                ret.w[1] = 2;
                ret.w[0] = 31;
                return ret;
            }
            ProcPostMessage(proc, 28, 0);
            ret.w[1] = 1;
            ret.w[0] = 30 / frameRetraces;
            SetGameView(3, 1);
            applause++;
            return ret;
        case 15:
            ProcPostEvent(24);
            if (finalSpin == 1) {
                task = CreatProc(CpuFinalSpinTurnProc, proc->data->playerProc.player | 0x2030400);
                task->data->playerProc.player = proc->data->playerProc.player;
                task->data->playerProc.skill = proc->data->playerProc.skill;
                ret.w[1] = 2;
                ret.w[0] = 31;
                return ret;
            }
            ProcPostMessage(proc, 12, 0);
            ret.w[1] = 1;
            ret.w[0] = 60 / frameRetraces;
            SetGameView(3, 1);
            return ret;
        case 28:
            if (finalSpin == 1) {
                task = CreatProc(CpuFinalSpinTurnProc, proc->data->playerProc.player | 0x2030400);
                task->data->playerProc.player = proc->data->playerProc.player;
                task->data->playerProc.skill = proc->data->playerProc.skill;
                ret.w[1] = 2;
                ret.w[0] = 31;
                return ret;
            }
            CpuChooseAction(proc);
            ret.w[1] = 1;
            ret.w[0] = 60 / frameRetraces;
            return ret;
        case 12:
            if (guRandom() % 100 < 33) {
                PlaySound(players[curPlayer].unk_100);
            }
            jackpotWon = 0;
            task = FindProc(0x5000000, -1);
            ProcPostMessage(task, 23, 0);
            task = CreatProc(CpuSpinProc, proc->data->playerProc.player | 0x2000100);
            task->data->playerProc.player = proc->data->playerProc.player;
            task->data->playerProc.skill = proc->data->playerProc.skill;
            ret.w[1] = 2;
            ret.w[0] = 3;
            return ret;
        case 13:
            PlaySound(players[curPlayer].unk_104);
            jackpotWon = 0;
            task = FindProc(0x5000000, -1);
            ProcPostMessage(task, 23, 0);
            task = CreatProc(CpuBuyVowelProc, proc->data->playerProc.player | 0x2000200);
            task->data->playerProc.player = proc->data->playerProc.player;
            task->data->playerProc.skill = proc->data->playerProc.skill;
            ret.w[1] = 2;
            ret.w[0] = 9;
            return ret;
        case 14:
            PlaySound(players[curPlayer].unk_108);
            task = FindProc(0x5000000, -1);
            ProcPostMessage(task, 23, 0);
            task = CreatProc(CpuSolveProc, proc->data->playerProc.player | 0x2000300);
            task->data->playerProc.player = proc->data->playerProc.player;
            task->data->playerProc.skill = proc->data->playerProc.skill;
            ret.w[1] = 2;
            ret.w[0] = 10;
            return ret;
        case 37:
            jackpotWon = 0;
            task = FindProc(0x5000000, -1);
            curLetter = '3';
            ProcPostMessage(task, 27, 1);
            ProcPostMessage(proc, 38, 0);
            ret.w[1] = 1;
            ret.w[0] = 60 / frameRetraces;
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
        case 34:
            ret.w[1] = 0;
            ret.w[0] = 0;
            return ret;
        }
    }
    return ret;
}
