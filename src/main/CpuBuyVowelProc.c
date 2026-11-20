#include "wof.h"

struct procResult_s CpuBuyVowelProc(proc_t *proc) {
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
    for (;;) {
        event = ProcGetMessage(proc);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 8:
            if (players[curPlayer].unk_000 < 250) {
                ProcPostMessage(proc, 51, 0);
                PlaySound(1);
                ret.w[1] = 1;
                ret.w[0] = 30 / frameRetraces;
                return ret;
            } else {
                SetGameView(3, 1);
                StartCpuLetterPick(CpuPickVowel(proc->data->playerProc.unk_0C) & 255);
                ProcPostMessage(proc, 5, 0);
                ret.w[1] = 1;
                ret.w[0] = 60 / frameRetraces;
                return ret;
            }
            break;
        case 5:
            PlaySound(players[curPlayer].unk_0FC + (curLetter - 'A'));
            ProcPostMessage(proc, 44, 0);
            ret.w[1] = 1;
            ret.w[0] = 30 / frameRetraces;
            return ret;
        case 44:
            task = FindProc(0x5010000, -1);
            ProcPostMessage(task, 23, 0);
            if (CallLetter(curLetter, 1) > 0) {
                ShowLetter(curLetter);
                task = CreatProc(LightLetterProc, 0x1000000);
                task->data->data80010574.letter = curLetter;
                ret.w[1] = 2;
                ret.w[0] = 6;
            } else {
                PlaySound(1);
                if (LoseTurn() != 0) {
                    ProcPostEvent(9);
                    ProcPostEvent(24);
                }
                ret.w[1] = 0;
                ret.w[0] = 0;
                return ret;
            }
            break;
        case 51:
            ProcPostEvent(9);
            PlaySound(150);
            // RULE-EXCEPTION: R25, no prototype in scope: retail passes the 0.8 as a double
            StartRumble(players[curPlayer].unk_014, 30, 0.8);
            LoseTurn();
            ret.w[1] = 0;
            ret.w[0] = 0;
            return ret;
        case 6:
            ProcPostEvent(24);
            ProcPostEvent(9);
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
