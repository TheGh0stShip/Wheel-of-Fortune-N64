// wof_cpu.c -- the machine's turn: its letters, its choice of solving, spinning or buying a vowel, its
// spin, vowel, solve and final spin, and its turn procs for the demo and a game
//
// PickHitLetter, CpuPickConsonant, CpuSpinProc, CpuBuyVowelProc, CpuFinalSpinTurnProc and AddDemoCpu
// each end off an 8-byte boundary with the next function right after, which happens only inside an
// object, and CpuPickVowel's read-only items run on into CpuChooseAction's with no 8-byte boundary
// between. The joins after CpuChooseAction, CpuSolveProc and CpuTurnProc rest on the RCS premise (every
// object from 0x8000BAA8 on opens its read-only data with an RCS run, which the project accepts): no
// run lies where an object starting there would need one. Its read-only data opens with the RCS run at
// 0x800011B0, which could open an object starting after InitPlayers, InitCpuLetters or PickMissLetter;
// where it ends after AddCpu the text does not say (the RCS run at 0x800014B8 opens the next object
// after AddCpu or one of the movie functions after it).

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

/*
=====================
CpuSpinProc

The machine spins.
=====================
*/
struct procResult_s CpuSpinProc(proc_t *proc) {
    struct procResult_s result;
    proc_t *task;
    obj_t *target;
    s32 event;

    result.w[1] = 1;
    result.w[0] = 0;
    if (proc->data->playerProc.player != curPlayer) {
        ProcClearMessages(proc);
        return result;
    }
    for (;;) {
        event = ProcGetMessage(proc);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 8:
            SetGameView(0, 1);
            task = CreatProc(WheelSpinProc, 0x4000000);
            target = FindObj(0x4010000, 0xFFFF0000);
            task->data->wheelSpin.wheel = target;
            task->data->wheelSpin.speed = (f32)(guRandom() % 50 + 100);
            if ((f64)task->data->wheelSpin.speed > 80.0) {
                ProcPostMessage(proc, 7, 0);
                result.w[1] = 1;
                result.w[0] = 30 / frameRetraces;
                return result;
            } else {
                result.w[1] = 2;
                result.w[0] = -1;
                return result;
            }
            break;
        case 7:
            if (Random(100) >= 76) {
                SetGameView(15, 1);
            } else {
                SetGameView(3, 1);
            }
            result.w[1] = 2;
            result.w[0] = 4;
            return result;
            break;
        case 4:
            SetGameView(0, 1);
            result.w[1] = 2;
            result.w[0] = 2;
            return result;
            break;
        case 2:
            target = FindObj(0x4010000, 0xFFFF0000);
            ApplyWedge(0);
            if (GetWedgeValue() == -1) {
                SetContestantsStill();
                SetGameView(0, 1);
                if (LoseTurn() != 0) {
                    ProcPostEvent(3);
                    ProcPostEvent(24);
                }
                result.w[1] = 0;
                result.w[0] = 0;
                return result;
            } else {
                if (GetWedgeValue() == -2) {
                    SetContestantsStill();
                    SetGameView(0, 1);
                    if (MustLoseTurn() != 0) {
                        PlayMovieCorner(12, 16);
                        result.w[1] = 2;
                        result.w[0] = 16;
                        return result;
                    }
                    LoseTurn();
                    result.w[1] = 0;
                    result.w[0] = 0;
                    return result;
                }
            }
            PlayContestantAnims();
            SetGameView(3, 1);
            StartCpuLetterPick(CpuPickConsonant(proc->data->playerProc.skill, proc) & 255);
            ProcPostMessage(proc, 5, 0);
            result.w[1] = 1;
            result.w[0] = 60 / frameRetraces;
            return result;
        case 16:
            LoseTurn();
            ProcPostEvent(3);
            ProcPostEvent(24);
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        case 5:
            PlaySound(players[curPlayer].letterSounds + (curLetter - 65));
            ProcPostMessage(proc, 44, 0);
            result.w[1] = 1;
            result.w[0] = 30 / frameRetraces;
            return result;
        case 44:
            ShowJackpot();
            task = FindProc(0x5010000, -1);
            ProcPostMessage(task, 23, 0);
            if (CallLetter(curLetter, 0) > 0) {
                ShowLetter(curLetter);
                task = CreatProc(LightLetterProc, 0x1000000);
                task->data->lightLetter.letter = curLetter;
                result.w[1] = 2;
                result.w[0] = 6;
                return result;
            } else {
                PlaySound(1);
                if (LoseTurn() != 0) {
                    ProcPostEvent(3);
                    ProcPostEvent(24);
                }
                result.w[1] = 0;
                result.w[0] = 0;
                return result;
            }
            break;
        case 6:
            if (GetWedgeValue() == -3) {
                jackpotWon = 1;
            }
            ProcPostEvent(24);
            ProcPostEvent(3);
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
CpuBuyVowelProc

The machine buys a vowel.
=====================
*/
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
            if (players[curPlayer].score < 250) {
                ProcPostMessage(proc, 51, 0);
                PlaySound(1);
                ret.w[1] = 1;
                ret.w[0] = 30 / frameRetraces;
                return ret;
            } else {
                SetGameView(3, 1);
                StartCpuLetterPick(CpuPickVowel(proc->data->playerProc.skill) & 255);
                ProcPostMessage(proc, 5, 0);
                ret.w[1] = 1;
                ret.w[0] = 60 / frameRetraces;
                return ret;
            }
            break;
        case 5:
            PlaySound(players[curPlayer].letterSounds + (curLetter - 'A'));
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
                task->data->lightLetter.letter = curLetter;
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
            StartRumble(players[curPlayer].controller, 30, 0.8);
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

/*
=====================
CpuSolveProc

The machine solves.
=====================
*/
struct procResult_s CpuSolveProc(proc_t *proc) {
    struct procResult_s result;
    proc_t *task;
    s32 unused;  /* NOTE: unused in the original */
    s32 event;

    result.w[1] = 1;
    result.w[0] = 0;
    if (proc->data->playerProc.player != curPlayer) {
        ProcClearMessages(proc);
        return result;
    }
    task = FindProc(0x1020000, -1);
    while ((event = ProcGetMessage(proc)) != 0) {
        switch (event) {
        case 8:
            StartSolvePuzzle();
            SetGameView(3, 1);
            result.w[1] = 2;
            result.w[0] = 5;
            return result;
        case 5:
            if (CheckSolve() == 1) {
                ProcPostMessage(task, 19, 0);
                ProcPostEvent(24);
                ProcPostEvent(10);
                result.w[1] = 0;
                result.w[0] = 0;
            } else {
                ProcPostMessage(task, 20, 0);
                PlaySound(1);
                if (LoseTurn() != 0) {
                    ProcPostEvent(10);
                    ProcPostEvent(24);
                }
                result.w[1] = 0;
                result.w[0] = 0;
                return result;
            }
            break;
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

/*
=====================
AddDemoCpu

A machine turn proc for the demo, of skill 0.65.
=====================
*/
void AddDemoCpu(s32 player) {
    proc_t *task;
    s32 unused;   /* NOTE: unused in the original */
    s32 unused2;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    task = CreatProc(CpuTurnProc, player | 0x2030000);
    task->data->playerProc.player = player;
    task->data->playerProc.skill = 0.65f;
    players[player].controller = 4;
    SetContestantSounds(player);
}

/*
=====================
AddCpu

A machine turn proc of the skill chosen.
=====================
*/
void AddCpu(s32 player) {
    proc_t *task;
    s32 unused;   /* NOTE: unused in the original */
    s32 unused2;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    task = CreatProc(CpuTurnProc, player | 0x2030000);
    task->data->playerProc.player = player;
    task->data->playerProc.skill = cpuSkill;
}
