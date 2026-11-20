#include "wof.h"


obj_t *func_80015848(proc_t *proc, Gfx *arg1, objDraw_t draw, s32 arg3) {
    obj_t *obj;
    s32 parent;

    parent = 0;
    if (proc != 0) {
        parent = proc->unk_04;
    }
    obj = func_8000B3B0(parent, draw, arg3);
    if (obj == 0) {
        return obj;
    }
    if (proc != 0) {
        proc->unk_30->obj = obj;
    }
    obj->scale = 1.0f;
    obj->x = 0;
    obj->y = 0;
    obj->z = 0;
    obj->unk_28 = 0;
    obj->unk_2C = 0;
    obj->unk_30 = 0;
    obj->unk_48 = arg1;
    return obj;
}
