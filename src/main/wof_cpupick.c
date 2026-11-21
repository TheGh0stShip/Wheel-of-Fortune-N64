// wof_cpupick.c -- the machine's letters and its choice of solving, spinning or buying a vowel
//
// PickHitLetter and CpuPickConsonant each end off an 8-byte boundary with the next function right
// after, which happens only inside an object, and CpuPickVowel's read-only items run on into
// CpuChooseAction's with no 8-byte boundary between. Whether PickMissLetter before it and CpuSpinProc
// after it are this object's the text does not say.

#include "wof.h"

// The #ident line of the system header this object included: the original assembler put the string
// into the read-only data, which it opens. The header is not in this tree, so its line stands here.
#ident "$Revision: 1.17 $"

/*
=====================
PickHitLetter

The last letter of a string that is in the puzzle, or else PickMissLetter's.
=====================
*/
s32 PickHitLetter(u8 *letters) {
    s32 i;
    s32 len;
    u8 c;

    c = ' ';
    len = StrLen(letters);
    for (i = 0; i < len; i++) {
        if (CountLetter(letters[i]) > 0) {
            c = letters[i];
            break;
        }
    }
    if (c == ' ') {
        c = PickMissLetter(letters);
    }
    return c;
}

/*
=====================
CpuPickConsonant

The machine's consonant: a right one with the chance of its skill.
=====================
*/
s32 CpuPickConsonant(f32 skill, proc_t *proc) {
    f32 roll;
    u8 result;

    RemoveCalledLetters(cpuConsonants);
    roll = Random(100);
    roll = roll / 100.0f;
    if (roll < skill) {
        result = PickHitLetter(cpuConsonants);
    } else {
        result = PickMissLetter(cpuConsonants);
        if (result == 32) {
            result = PickHitLetter(cpuConsonants);
        }
    }
    return result;
}

/*
=====================
CpuPickVowel

The machine's vowel: a right one with the chance of its skill.
=====================
*/
s32 CpuPickVowel(f32 skill) {
    f32 roll;
    u8 result;

    RemoveCalledLetters(cpuVowels);
    roll = (f32)Random(100);
    roll = roll / 100.0f;
    if (roll < skill) {
        result = PickHitLetter(cpuVowels);
    } else {
        result = PickMissLetter(cpuVowels);
        if (result == 32) {
            result = PickHitLetter(cpuVowels);
        }
    }
    return result;
}

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
