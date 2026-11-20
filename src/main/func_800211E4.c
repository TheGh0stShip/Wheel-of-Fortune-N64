#include "wof.h"


obj_t *func_800211E4(proc_t *proc, char *arg1, f32 x, f32 y, s32 arg4) {
    s32 parent;
    obj_t *obj;

    parent = 0;
    if (proc != 0) {
        parent = proc->unk_04;
    }
    obj = (obj_t *)func_8000B3B0(parent, (s32)&func_80020150, 0x5010000);
    obj->scale = 1.0f;
    obj->x = x;
    obj->y = y;
    obj->z = 0;
    obj->unk_28 = 0;
    obj->unk_2C = 0;
    obj->unk_30 = 0;
    obj->unk_48 = 0;
    return obj;
}
