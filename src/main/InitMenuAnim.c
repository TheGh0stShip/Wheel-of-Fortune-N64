#include "wof.h"

/*
=====================
InitMenuAnim

InitAnim for a contestant shown in the menus, with its obj; prints InitAnim's first message.
=====================
*/
void InitMenuAnim(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    proc_t *task;
    obj_t *obj;

    if (arg0 < 0) {
        return;
    }
    if (arg0 >= 6) {
        func_80009F38("InitAnim: invalid animation number");
    }
    if (menuClips[arg0].pictures == 0) {
        return;
    }
    task = FindProc(arg1 | 0xA000300, -1);
    if (task != 0) {
        KillProc(task, 0);
    }
    task = CreatProc(AnimProc, arg1 | 0xA000300);
    obj = MakeObj(task, D_0113A9B0, DrawMenuContestant, arg1 | 0xA020000);
    obj->secondDl = D_0113A9D0;
    obj->x = arg2;
    obj->y = arg3;
    obj->z = arg4;
    task->data->anim.slot = arg1;
    task->data->anim.pictures = menuClips[arg0].pictures;
    task->data->anim.count = menuClips[arg0].count;
    task->data->anim.loop = menuClips[arg0].loop;
    task->data->anim.obj = obj;
}
