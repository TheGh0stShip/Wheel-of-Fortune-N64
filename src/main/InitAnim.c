// InitAnim.c -- starts a player's contestant playing one of its two animations

#include "wof.h"

/*
=====================
InitAnim

Starts a player's contestant playing one of its two animations.
=====================
*/
void InitAnim(s32 anim, s32 player) {
    proc_t *task;
    obj_t *obj;
    s32 kind;

    if (anim < 0) {
        return;
    }
    if (anim >= 2) {
        func_80009F38("InitAnim: invalid animation number");
    }
    kind = players[player].contestant;
    if (kind >= 6) {
        func_80009F38("InitAnim: invalid contestant number");
    }
    if (contestantClips[kind][anim].pictures == 0) {
        return;
    }
    obj = FindObj(player | 0xA020000, -1);
    if (obj == 0) {
        func_80009F38("InitAnim: cannot find contestant obj");
    }
    task = FindProc(player | 0xA000300, -1);
    if (task != 0) {
        KillProc(task, 0);
    }
    task = CreatProc(AnimProc, player | 0xA000300);
    task->data->anim.slot = player;
    task->data->anim.pictures = contestantClips[kind][anim].pictures;
    task->data->anim.count = contestantClips[kind][anim].count;
    task->data->anim.loop = contestantClips[kind][anim].loop;
    task->data->anim.obj = obj;
}
