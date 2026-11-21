// wof_confetti.c -- confetti: a piece at a random place, a burst of them, and the celebration
//
// The joins after AddConfetti and ConfettiBurstProc rest on the RCS premise (every object from
// 0x8000BAA8 on opens its read-only data with an RCS run, which the project accepts): no run lies where
// an object starting there would need one. The game's text ends after StartCelebration. Its read-only
// data opens with the RCS run at 0x80001A60, which could open an object starting after StartApplause,
// DrawConfetti or ConfettiProc; where it starts the text does not say.

#include "wof.h"

// The #ident line of the system header this object included: the original assembler put the string
// into the read-only data, which it opens. The header is not in this tree, so its line stands here.
#ident "$Revision: 1.17 $"

/*
=====================
AddConfetti

A piece of confetti at a random place, speed and count of turns.
=====================
*/
void AddConfetti(s32 x, s32 xRange, s32 y, s32 yRange, s32 speedRange, s32 speedBase, s32 turnsRange, s32 turnsBase) {
    obj_t *obj;
    proc_t *task;

    task = CreatProc(ConfettiProc, 0x5030000);
    obj = MakeObj(task, 0, DrawConfetti, 0x5030000);
    task->data->confetti.count = guRandom() % turnsRange - turnsBase + turnsBase;
    task->data->confetti.vx = (f32)(guRandom() % speedRange - speedBase + speedBase) / 100.0f;
    task->data->confetti.vy = 0;
    task->data->confetti.x = guRandom() % xRange + x;
    task->data->confetti.y = guRandom() % yRange + y;
}

/*
=====================
ConfettiBurstProc

Throws confetti for a while.
=====================
*/
struct procResult_s ConfettiBurstProc(proc_t *proc) {
    struct procResult_s result;
    s32 event;
    s32 i;
    obj_t *obj;

    obj = proc->data->obj;
    for (;;) {
        event = ProcGetMessage(proc);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 8:
            proc->data->confettiBurst.countdown = 10;
            break;
        }
    }
    proc->data->confettiBurst.countdown--;
    if (proc->data->confettiBurst.countdown < 0) {
        if (proc->data->confettiBurst.countdown < -40) {
            result.w[1] = 0;
            result.w[0] = 1;
            return result;
        }
        if (proc->data->confettiBurst.countdown >= -9) {
            AddConfetti(80, 150, 60, 80, 30, 10, 2, 1);
        } else {
            AddConfetti(80, 150, 60, 80, 30, 10, 2, 1);
            result.w[1] = 1;
            result.w[0] = ((guRandom() % -1) * proc->data->confettiBurst.countdown) / frameRetraces;
            return result;
        }
    } else {
        i = 0;
        for (;;) {
            if (i >= 4) {
                break;
            }
            AddConfetti(52, 15, 27, 15, 300, 150, 6, 3);
            i++;
        }
    }
    result.w[1] = 1;
    result.w[0] = (guRandom() % 10) / frameRetraces;
    return result;
}

/*
=====================
StartCelebration

The movie and the confetti of a win.
=====================
*/
void StartCelebration(void) {
    curMask = celebrationMask;
    PlayMovie(0x16, 0, 0x28, 0xF);
    CreatProc(ConfettiBurstProc, 0x05030000);
}
