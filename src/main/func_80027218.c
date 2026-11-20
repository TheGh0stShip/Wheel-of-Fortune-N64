#include "wof.h"


s32 func_80027218(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    obj_t *obj;
    s32 sp14;

    sp14 = 0;
    if (arg0 != 0) {
        sp14 = ((proc_t *)arg0)->unk_04;
    }
    obj = (obj_t *)func_8000B3B0(sp14, arg2, arg3);
    if (obj == 0) {
        return (s32)obj;
    }
    if (arg0 != 0) {
        *(obj_t **)((proc_t *)arg0)->unk_30 = obj;
    }
    obj->scale = 1.0f;
    obj->x = -160;
    obj->y = -80;
    obj->z = -450;
    obj->unk_28 = 0;
    obj->unk_2C = 0;
    obj->unk_30 = 0;
    obj->unk_48 = arg1;
    return (s32)obj;
}
