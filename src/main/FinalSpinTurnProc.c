#include "wof.h"
#include "rumble.h"


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
            func_80029974(0);
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
