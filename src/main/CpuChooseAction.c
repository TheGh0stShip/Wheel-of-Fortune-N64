// CpuChooseAction.c -- the machine decides to solve, spin or buy a vowel

#include "wof.h"

/*
=====================
CpuChooseAction

The machine decides to solve, spin or buy a vowel.
=====================
*/
void CpuChooseAction(proc_t *proc) {
    proc_t *task;
    s32 sp14;
    f32 score;
    f32 roll;
    f32 done;

    sp14 = 0;
    done = CheckPercentDone();
    task = FindProc(0x5000000, -1);
    if (canSolve != 0) {
        if (jackpotWon != 0) {
            if (done > 0.6) {
                curLetter = 50;
                ProcPostMessage(proc, 14, 0);
                ProcPostMessage(task, 27, 0);
                return;
            }
        }
        if (done > 0.7 || canSpin == 0) {
            curLetter = 50;
            ProcPostMessage(proc, 14, 0);
            ProcPostMessage(task, 27, 0);
            return;
        }
    }
    if (canSpin != 0) {
        roll = (f32)Random(100);
        roll = roll / 100.0f;
        score = (f32)StrLen(cpuConsonants);
        score = score / 21.0f;
        score = score * 0.15;
        score = score + roll;
        switch (GetUncalledKinds()) {
        case 4:
            if (score < proc->data->playerProc.skill || players[curPlayer].score < 250) {
                curLetter = 48;
                ProcPostMessage(proc, 12, 0);
            } else {
                curLetter = 49;
                ProcPostMessage(proc, 13, 0);
            }
            break;
        case 3:
            curLetter = 48;
            ProcPostMessage(proc, 12, 0);
            break;
        case 2:
            curLetter = 49;
            ProcPostMessage(proc, 13, 0);
            break;
        }
    } else if (canBuyVowel != 0) {
        if (StrLen(cpuVowels) != 0) {
            curLetter = 49;
            ProcPostMessage(proc, 13, 0);
        } else {
            curLetter = 48;
            ProcPostMessage(proc, 12, 0);
        }
    }
    ProcPostMessage(task, 27, 0);
}
