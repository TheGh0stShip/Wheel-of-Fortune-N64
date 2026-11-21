// BuyVowelProc.c -- a person buys a vowel for 250

#include "wof.h"
#include "rumble.h"

/*
=====================
BuyVowelProc

A person buys a vowel for 250.
=====================
*/
struct procResult_s BuyVowelProc(proc_t *proc) {
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
            if (players[curPlayer].score < 250) {
                ProcPostMessage(proc, 51, 0);
                PlaySound(1);
                StartRumble(players[curPlayer].controller, 30, 0.8f);
                ret.w[1] = 1;
                ret.w[0] = 30 / frameRetraces;
                return ret;
            } else {
                if (GetUncalledKinds() == 3) {
                    PlayMovieCorner(1, 16);
                    ret.w[1] = 2;
                    ret.w[0] = 16;
                    return ret;
                } else {
                    SetGameView(3, 0);
                    StartLetterPick();
                    ret.w[1] = 2;
                    ret.w[0] = 5;
                }
            }
            break;
        case 16:
            ProcPostEvent(9);
            ret.w[1] = 0;
            ret.w[1] = 0;
            return ret;
        case 5:
            PlaySound(players[curPlayer].letterSounds + (curLetter - 'A'));
            ProcPostMessage(proc, 44, 0);
            ret.w[1] = 1;
            ret.w[0] = 30 / frameRetraces;
            return ret;
        case 44:
            if (CallLetter(curLetter, 1) > 0) {
                ShowLetter(curLetter);
                task = CreatProc(LightLetterProc, 0x1000000);
                task->data->lightLetter.letter = curLetter;
                ret.w[1] = 2;
                ret.w[0] = 6;
            } else {
                PlaySound(1);
                StartRumble(players[curPlayer].controller, 30, 0.8f);
                if (LoseTurn() != 0) {
                    ProcPostEvent(9);
                }
                ret.w[1] = 0;
                ret.w[0] = 0;
                return ret;
            }
            break;
        case 51:
            ProcPostMessage(proc, 52, 0);
            PlaySound(150);
            ret.w[1] = 1;
            ret.w[0] = 60 / frameRetraces;
            return ret;
        case 52:
            ProcPostEvent(9);
            LoseTurn();
            ret.w[1] = 0;
            ret.w[0] = 0;
            return ret;
        case 6:
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
