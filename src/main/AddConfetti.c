#include "wof.h"


/*
=====================
AddConfetti

A piece of confetti at a random place, speed and count of turns.
=====================
*/
void AddConfetti(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    obj_t *sp10;
    proc_t *task;

    task = CreatProc(ConfettiProc, 0x5030000);
    sp10 = MakeObj(task, 0, DrawConfetti, 0x5030000);
    task->data->confetti.count = guRandom() % arg6 - arg7 + arg7;
    task->data->confetti.vx = (f32)(guRandom() % arg4 - arg5 + arg5) / 100.0f;
    task->data->confetti.vy = 0;
    task->data->confetti.x = guRandom() % arg1 + arg0;
    task->data->confetti.y = guRandom() % arg3 + arg2;
}
