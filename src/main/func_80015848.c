#include "wof.h"


obj_t *func_80015848(proc_t *proc, s32 arg1, s32 arg2, s32 arg3) {
    obj_t *obj;
    s32 parent;

    parent = 0;
    if (proc != 0) {
        parent = proc->unk_04;
    }
    obj = (obj_t *)func_8000B3B0(parent, arg2, arg3);
    if (obj == 0) {
        return obj;
    }
    if (proc != 0) {
        *(obj_t **)proc->unk_30 = obj;
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
