// InitMenuAnim.c -- initAnim for a contestant shown in the menus, with its obj; prints InitAnim's
// first message

#include "wof.h"

/*
=====================
InitMenuAnim

InitAnim for a contestant shown in the menus, with its obj; prints InitAnim's first message.
=====================
*/
void InitMenuAnim(s32 contestant, s32 slot, s32 x, s32 y, s32 z) {
    proc_t *task;
    obj_t *obj;

    if (contestant < 0) {
        return;
    }
    if (contestant >= 6) {
        FatalError("InitAnim: invalid animation number");
    }
    if (menuClips[contestant].pictures == 0) {
        return;
    }
    task = FindProc(slot | 0xA000300, -1);
    if (task != 0) {
        KillProc(task, 0);
    }
    task = CreatProc(AnimProc, slot | 0xA000300);
    obj = MakeObj(task, D_0113A9B0, DrawMenuContestant, slot | 0xA020000);
    obj->secondDl = D_0113A9D0;
    obj->x = x;
    obj->y = y;
    obj->z = z;
    task->data->anim.slot = slot;
    task->data->anim.pictures = menuClips[contestant].pictures;
    task->data->anim.count = menuClips[contestant].count;
    task->data->anim.loop = menuClips[contestant].loop;
    task->data->anim.obj = obj;
}
