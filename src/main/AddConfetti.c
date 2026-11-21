#include "wof.h"


void AddConfetti(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    obj_t *sp10;
    proc_t *task;

    task = CreatProc(ConfettiProc, 0x5030000);
    sp10 = MakeObj(task, 0, DrawConfetti, 0x5030000);
    task->data->data80034028.count = guRandom() % arg6 - arg7 + arg7;
    task->data->data80034028.vx = (f32)(guRandom() % arg4 - arg5 + arg5) / 100.0f;
    task->data->data80034028.vy = 0;
    task->data->data80034028.x = guRandom() % arg1 + arg0;
    task->data->data80034028.y = guRandom() % arg3 + arg2;
}
