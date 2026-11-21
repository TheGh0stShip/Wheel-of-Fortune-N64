// CpuFinalSpinTurnProc.c -- the machine's turn in the final spin

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
