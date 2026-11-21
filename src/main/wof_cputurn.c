// wof_cputurn.c -- the machine's turn in the final spin and in a round
//
// CpuFinalSpinTurnProc ends off an 8-byte boundary with CpuTurnProc right after, which happens only
// inside an object. Whether CpuSolveProc before it and AddDemoCpu after it are this object's the text
// does not say.

#include "wof.h"

/*
=====================
CpuFinalSpinTurnProc

The machine's turn in the final spin.
=====================
*/
struct procResult_s CpuFinalSpinTurnProc(proc_t *proc) {
    struct procResult_s result;
    proc_t *task;
    s32 unused;  /* NOTE: unused in the original */
    s32 event;
    f32 ratio;

    result.w[1] = 1;
    result.w[0] = 0;
    if (proc->data->playerProc.player != curPlayer) {
        ProcClearMessages(proc);
        return result;
    }
    task = FindProc(0x5000000, -1);
    while ((event = ProcGetMessage(proc)) != 0) {
        switch (event) {
        case 8:
            SetGameView(3, 1);
            switch (GetHiddenKinds()) {
            case 4:
                if (Random(100) >= 11) {
                    StartCpuLetterPick(CpuPickConsonant(proc->data->playerProc.skill, proc) & 255);
                } else {
                    StartCpuLetterPick(CpuPickVowel(proc->data->playerProc.skill) & 255);
                }
                break;
            case 2:
                StartCpuLetterPick(CpuPickVowel(proc->data->playerProc.skill) & 255);
                break;
            case 3:
                StartCpuLetterPick(CpuPickConsonant(proc->data->playerProc.skill, proc) & 255);
                break;
            }
            ProcPostMessage(proc, 5, 0);
            result.w[1] = 1;
            result.w[0] = 60 / frameRetraces;
            return result;
            break;
        case 5:
            PlaySound(players[curPlayer].letterSounds + (curLetter - 65));
            ProcPostMessage(proc, 44, 0);
            result.w[1] = 1;
            result.w[0] = 30 / frameRetraces;
            return result;
        case 44:
            task = FindProc(0x5010000, -1);
            ProcPostMessage(task, 23, 0);
            if (CallLetter(curLetter, 2) > 0) {
                ShowLetter(curLetter);
                task = CreatProc(LightLetterProc, 0x1000000);
                task->data->lightLetter.letter = curLetter;
                result.w[1] = 2;
                result.w[0] = 6;
                return result;
            } else {
                PlaySound(1);
                LoseTurn();
                ProcPostEvent(24);
                ProcPostEvent(31);
                ProcPostMessage(task, 31, 0);
                result.w[1] = 0;
                result.w[0] = 0;
                return result;
            }
        case 6:
            SetScorePictures(0);
            StartSolveTimer();
            ratio = CheckPercentDone();
            if (ratio > 0.7) {
                task = CreatProc(CpuSolveProc, proc->data->playerProc.player | 0x2000300);
                task->data->playerProc.player = proc->data->playerProc.player;
                task->data->playerProc.skill = proc->data->playerProc.skill;
                result.w[1] = 2;
                result.w[0] = 10;
                return result;
            } else {
                result.w[1] = 1;
                result.w[0] = 0;
                return result;
            }
        case 33:
            PlaySound(1);
        case 10:
            if (CheckSolve() != 1) {
                LoseTurn();
            }
            ProcPostEvent(24);
            ProcPostEvent(31);
            ProcPostMessage(task, 31, 0);
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        case 34:
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        }
    }
    return result;
}

/*
=====================
CpuTurnProc

The turn of the machine: makes the procs of its steps.
=====================
*/
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
            PlaySound(players[curPlayer].freeSpinSound);
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
            if (vowelsOnlyAnnounced == 0 && GetHiddenKinds() == 2) {
                vowelsOnlyAnnounced = 1;
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
