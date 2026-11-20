#include "wof.h"


struct procResult_s CpuFinalSpinTurnProc(proc_t *proc) {
    struct procResult_s sp10;
    proc_t *task;
    s32 unused;  /* NOTE: unused in the original */
    s32 event;
    f32 ratio;

    sp10.w[1] = 1;
    sp10.w[0] = 0;
    if (proc->data->playerProc.player != curPlayer) {
        ProcClearMessages(proc);
        return sp10;
    }
    task = FindProc(0x5000000, -1);
    while ((event = ProcGetMessage(proc)) != 0) {
        switch (event) {
        case 8:
            SetGameView(3, 1);
            switch (GetHiddenKinds()) {
            case 4:
                if (Random(100) >= 11) {
                    StartCpuLetterPick(CpuPickConsonant(proc->data->playerProc.unk_0C, proc) & 255);
                } else {
                    StartCpuLetterPick(CpuPickVowel(proc->data->playerProc.unk_0C) & 255);
                }
                break;
            case 2:
                StartCpuLetterPick(CpuPickVowel(proc->data->playerProc.unk_0C) & 255);
                break;
            case 3:
                StartCpuLetterPick(CpuPickConsonant(proc->data->playerProc.unk_0C, proc) & 255);
                break;
            }
            ProcPostMessage(proc, 5, 0);
            sp10.w[1] = 1;
            sp10.w[0] = 60 / frameRetraces;
            return sp10;
            break;
        case 5:
            PlaySound(players[curPlayer].unk_0FC + (curLetter - 65));
            ProcPostMessage(proc, 44, 0);
            sp10.w[1] = 1;
            sp10.w[0] = 30 / frameRetraces;
            return sp10;
        case 44:
            task = FindProc(0x5010000, -1);
            ProcPostMessage(task, 23, 0);
            if (CallLetter(curLetter, 2) > 0) {
                ShowLetter(curLetter);
                task = CreatProc(LightLetterProc, 0x1000000);
                task->data->data80010574.letter = curLetter;
                sp10.w[1] = 2;
                sp10.w[0] = 6;
                return sp10;
            } else {
                PlaySound(1);
                LoseTurn();
                ProcPostEvent(24);
                ProcPostEvent(31);
                ProcPostMessage(task, 31, 0);
                sp10.w[1] = 0;
                sp10.w[0] = 0;
                return sp10;
            }
        case 6:
            func_80029974(0);
            StartSolveTimer();
            ratio = CheckPercentDone();
            if (ratio > 0.7) {
                task = CreatProc(CpuSolveProc, proc->data->playerProc.player | 0x2000300);
                task->data->playerProc.player = proc->data->playerProc.player;
                task->data->playerProc.unk_0C = proc->data->playerProc.unk_0C;
                sp10.w[1] = 2;
                sp10.w[0] = 10;
                return sp10;
            } else {
                sp10.w[1] = 1;
                sp10.w[0] = 0;
                return sp10;
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
            sp10.w[1] = 0;
            sp10.w[0] = 0;
            return sp10;
        case 34:
            sp10.w[1] = 0;
            sp10.w[0] = 0;
            return sp10;
        }
    }
    return sp10;
}
