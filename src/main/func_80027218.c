#include "wof.h"


obj_t *func_80027218(proc_t *proc, Gfx *arg1, objDraw_t draw, s32 arg3) {
    obj_t *obj;
    s32 sp14;

    sp14 = 0;
    if (proc != 0) {
        sp14 = proc->id;
    }
    obj = CreatObj(sp14, draw, arg3);
    if (obj == 0) {
        return obj;
    }
    if (proc != 0) {
        proc->data->obj = obj;
    }
    obj->scale = 1.0f;
    obj->x = -160;
    obj->y = -80;
    obj->z = -450;
    obj->roll = 0;
    obj->pitch = 0;
    obj->heading = 0;
    obj->dl = arg1;
    return obj;
}
