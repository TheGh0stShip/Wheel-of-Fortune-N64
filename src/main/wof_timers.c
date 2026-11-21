// wof_timers.c -- the host's final spin when the time runs out, and the timers: of a round, of the
// demo, of a solve, and a five-second one, with the functions that start them
//
// RoundTimerProc, DemoTimerProc, StartFreeSpinTimer, StartSolveTimer and ResetSolveTimer each end off an
// 8-byte boundary with the next function right after, which happens only inside an object; a 4-byte gap
// ends the text after StartDemoTimer. The joins after FinalSpinProc, SolveTimerProc, FreeSpinTimerProc,
// StopFreeSpinTimer and StartRoundTimer rest on the RCS premise (every object from 0x8000BAA8 on opens its
// read-only data with an RCS run, which the project accepts): no run lies where an object starting
// there would need one. Its read-only data opens with the RCS run at 0x800018F8, which could open an
// object starting after any of SolvePuzzleProc to StartBonusRound; where it starts the text does not
// say.

#include "wof.h"

// The #ident line of the system header this object included: the original assembler put the string
// into the read-only data, which it opens. The header is not in this tree, so its line stands here.
#ident "$Revision: 1.17 $"


/*
=====================
FinalSpinProc

The host's final spin when the time runs out: "Final spin is ".
=====================
*/
struct procResult_s FinalSpinProc(proc_t *proc) {
    struct procResult_s result;
    proc_t *task;
    obj_t *node;
    s32 event;

    result.w[1] = 1;
    result.w[0] = 0;
    while ((event = ProcGetMessage(proc)) != 0) {
        switch (event) {
        case 8:
            ProcPostMessage(proc, 41, 0);
            result.w[1] = 1;
            result.w[0] = 180 / frameRetraces;
            return result;
        case 41:
            PlayMovieCorner(8, 44);
            result.w[1] = 2;
            result.w[0] = 44;
            return result;
        case 2:
            ApplyWedge(1);
            if (GetWedgeValue() <= 0 || GetWedgeValue() == 10000) {
                result.w[1] = 1;
                result.w[0] = 60 / frameRetraces;
                return result;
            }
            ProcPostEvent(32);
            PrintStr("Final spin is ");
            PrintNum(GetWedgeValue());
            PrintStr("\n");
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        }
    }
    SetGameView(0, 1);
    task = CreatProc(WheelSpinProc, 0x4000000);
    node = FindObj(0x4010000, 0xFFFF0000);
    task->data->wheelSpin.wheel = node;
    task->data->wheelSpin.speed = guRandom() % 25 + 75;
    result.w[1] = 2;
    result.w[0] = 2;
    return result;
}

/*
=====================
RoundTimerProc

The time of a round, 300 seconds a person and 240 the machine; then the final spin or the end.
=====================
*/
struct procResult_s RoundTimerProc(proc_t *proc) {
    struct procResult_s result;
    OSTime time; /* NOTE: unused in the original. Eight bytes nothing touches; guess: an OSTime */
    s32 event;
    s32 now;
    s32 i;

    result.w[1] = 1;
    result.w[0] = 0;
    for (;;) {
        event = ProcGetMessage(proc);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 8:
            roundTime = 0;
            i = 0;
            for (;;) {
                if (i >= 3) {
                    break;
                }
                if (players[i].controller == 4) {
                    roundTime = roundTime + 240;
                } else {
                    roundTime = roundTime + 300;
                }
                i++;
            }
        case 43:
            proc->data->timer.start = (s32)(osGetTime() / osClockRate);
            break;
        }
    }
    roundTime = roundTime + pausedTime;
    now = (s32)(osGetTime() / osClockRate);
    if ((now - proc->data->timer.start) >= roundTime) {
        if (FindProc(0x5010000, -1) != 0) {
            return result;
        }
        if (FindProc(0x5020000, -1) != 0) {
            return result;
        }
        if (FindProc(0x2000100, 0xFF00FF00) != 0) {
            return result;
        }
        if (FindProc(0x2000200, 0xFF00FF00) != 0) {
            return result;
        }
        if (FindProc(0x2000300, 0xFF00FF00) != 0) {
            return result;
        }
        if (FindProc(0x2000500, 0xFF00FF00) != 0) {
            return result;
        }
        if (FindProc(0x7050000, 0xFF00FF00) != 0) {
            return result;
        }
        if (((f64)CheckPercentDone()) < 0.6) {
            PlaySound(3);
            CreatProc(FinalSpinProc, 0x7020000);
            ProcPostMessageClass(30, 0, 0, 0);
        }
        gameOver = 1;
        result.w[1] = 0;
        result.w[0] = 0;
        return result;
    }
    return result;
}

/*
=====================
DemoTimerProc

Ends the demo after 30 seconds or on START.
=====================
*/
struct procResult_s DemoTimerProc(proc_t *proc) {
    struct procResult_s result;
    OSTime time; /* NOTE: unused in the original. Eight bytes nothing touches; guess: an OSTime */
    s32 event;
    s32 now;

    result.w[1] = 1;
    result.w[0] = 0;
    for (;;) {
        event = ProcGetMessage(proc);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 8:
            proc->data->timer.start = (s32)(osGetTime() / osClockRate);
            break;
        }
    }
    now = (s32)(osGetTime() / osClockRate);
    if (((now - proc->data->timer.start) >= 30) || (((buttonsPressed & 0x1000) & 0xFFFF) != 0)) {
        ProcPostMessageClass(34, 0, 0, 1);
        result.w[1] = 0;
    }
    return result;
}

/*
=====================
SolveTimerProc

The time to solve: 8 seconds, or 20 in the bonus round; then it posts message 33.
=====================
*/
struct procResult_s SolveTimerProc(proc_t *proc) {
    struct procResult_s result;
    OSTime time; /* NOTE: unused in the original. Eight bytes nothing touches; guess: an OSTime */
    s32 event;
    s32 now;

    result.w[1] = 1;
    result.w[0] = 0;
    for (;;) {
        event = ProcGetMessage(proc);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 8:
            proc->data->timer.start = (s32)(osGetTime() / osClockRate);
            break;
        }
    }
    proc->data->timer.start = proc->data->timer.start + pausedTime;
    now = (s32)(osGetTime() / osClockRate);
    if (gameMode == 4) {
        bonusTimeLeft = 20 - (now - proc->data->timer.start);
        if ((now - proc->data->timer.start) >= 20) {
            bonusTimeLeft = 0;
            ProcPostMessageClass(33, 0, 0, 0);
            result.w[1] = 0;
        }
    } else {
        if ((now - proc->data->timer.start) >= 8) {
            ProcPostMessageClass(33, 0, 0, 0);
            ProcPostEvent(33);
            result.w[1] = 0;
        }
    }
    return result;
}

/*
=====================
FreeSpinTimerProc

Gives a player who may use a free spin 5 seconds to choose; then event 48, and the turn is lost.
=====================
*/
struct procResult_s FreeSpinTimerProc(proc_t *proc) {
    struct procResult_s result;
    OSTime time; /* NOTE: unused in the original. Eight bytes nothing touches; guess: an OSTime */
    s32 event;
    s32 now;

    result.w[1] = 1;
    result.w[0] = 0;
    for (;;) {
        event = ProcGetMessage(proc);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 8:
            proc->data->timer.start = (s32)(osGetTime() / osClockRate);
            break;
        }
    }
    proc->data->timer.start = proc->data->timer.start + pausedTime;
    now = (s32)(osGetTime() / osClockRate);
    if ((now - proc->data->timer.start) >= 5) {
        ProcPostEvent(48);
        result.w[1] = 0;
    }
    return result;
}

/*
=====================
StartFreeSpinTimer

Starts FreeSpinTimerProc, when a player may use a free spin instead of losing the turn.
=====================
*/
void StartFreeSpinTimer(void) {
    CreatProc(FreeSpinTimerProc, 0x07050000);
}

/*
=====================
StopFreeSpinTimer

Stops FreeSpinTimerProc, when the player chooses to use the free spin.
=====================
*/
void StopFreeSpinTimer(void) {
    KillProcClass(0x07050000, -1, 0);
}

/*
=====================
StartSolveTimer

Creates SolveTimerProc.
=====================
*/
void StartSolveTimer(void) {
    CreatProc(SolveTimerProc, 0x07030000);
}

/*
=====================
ResetSolveTimer

Starts the solve timer over, in the final spin.
=====================
*/
void ResetSolveTimer(void) {
    proc_t *task;

    if (finalSpin == 0 || gameMode == 4) {
        return;
    }
    task = FindProc(0x7030000, -1);
    if (task == 0) {
        FatalError("ResetSolveTimer: Solve Timer Proc does not exist.\n");
    }
    ProcPostMessage(task, 8, 0);
}

/*
=====================
StartRoundTimer

Creates RoundTimerProc.
=====================
*/
void StartRoundTimer(void) {
    gameOver = 0;
    CreatProc(RoundTimerProc, 0x07010000);
}

/*
=====================
StartDemoTimer

Creates DemoTimerProc.
=====================
*/
void StartDemoTimer(void) {
    CreatProc(DemoTimerProc, 0x07040000);
}
