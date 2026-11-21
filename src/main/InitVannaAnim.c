// InitVannaAnim.c -- starts Vanna playing an animation; animation 80 is animation 2 of the bonus
// round

#include "wof.h"

/*
=====================
InitVannaAnim

Starts Vanna playing an animation; animation 80 is animation 2 of the bonus round.
=====================
*/
proc_t *InitVannaAnim(s32 anim, s32 replace) {
    proc_t *task;
    obj_t *child;
    s32 id;

    id = anim;
    if (anim < 0) {
        return;
    }
    if (anim == 80) {
        anim = 2;
    } else if (anim >= 6) {
        func_80009F38("InitVannaAnim: invalid animation number");
    }
    if (vannaClips[anim].pictures == 0) {
        return 0;
    }
    if (replace != 0) {
        KillProcClass(0xA000400, -1, 1);
        FreeObjClass(0xA030000, -1);
    }
    task = CreatProc(VannaAnimProc, 0xA000400);
    child = MakeObj(task, 0, DrawVanna, 0xA030000);
    child->x = vannaX;
    task->data->vannaAnim.anim = id;
    task->data->vannaAnim.pictures = vannaClips[anim].pictures;
    task->data->vannaAnim.count = vannaClips[anim].count;
    task->data->vannaAnim.unk_14 = vannaClips[anim].unk_0C;
    task->data->vannaAnim.loop = vannaClips[anim].loop;
    task->data->vannaAnim.mirror = vannaClips[anim].mirror;
    task->data->vannaAnim.obj = child;
    return task;
}
