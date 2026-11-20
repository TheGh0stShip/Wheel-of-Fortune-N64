#include "wof.h"


obj_t *func_80027218(proc_t *proc, Gfx *arg1, objDraw_t draw, s32 arg3) {
    obj_t *obj;
    s32 sp14;

    sp14 = 0;
    if (proc != 0) {
        sp14 = proc->unk_04;
    }
    obj = func_8000B3B0(sp14, draw, arg3);
    if (obj == 0) {
        return obj;
    }
    if (proc != 0) {
        proc->unk_30->obj = obj;
    }
    obj->scale = 1.0f;
    obj->x = -160;
    obj->y = -80;
    obj->z = -450;
    obj->unk_28 = 0;
    obj->unk_2C = 0;
    obj->unk_30 = 0;
    obj->unk_48 = arg1;
    return obj;
}
