#include "wof.h"

/*
=====================
InitAnim

Starts a player's contestant playing one of its two animations.
=====================
*/
void InitAnim(s32 arg0, s32 arg1) {
    proc_t *task;
    obj_t *obj;
    s32 kind;

    if (arg0 < 0) {
        return;
    }
    if (arg0 >= 2) {
        func_80009F38("InitAnim: invalid animation number");
    }
    kind = players[arg1].contestant;
    if (kind >= 6) {
        func_80009F38("InitAnim: invalid contestant number");
    }
    if (contestantClips[kind][arg0].pictures == 0) {
        return;
    }
    obj = FindObj(arg1 | 0xA020000, -1);
    if (obj == 0) {
        func_80009F38("InitAnim: cannot find contestant obj");
    }
    task = FindProc(arg1 | 0xA000300, -1);
    if (task != 0) {
        KillProc(task, 0);
    }
    task = CreatProc(AnimProc, arg1 | 0xA000300);
    task->data->anim.slot = arg1;
    task->data->anim.pictures = contestantClips[kind][arg0].pictures;
    task->data->anim.count = contestantClips[kind][arg0].count;
    task->data->anim.loop = contestantClips[kind][arg0].loop;
    task->data->anim.obj = obj;
}
