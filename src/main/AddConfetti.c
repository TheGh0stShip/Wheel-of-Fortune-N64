// AddConfetti.c -- a piece of confetti at a random place, speed and count of turns

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
