#include "wof.h"


struct n64dk_r12 func_8000F740(s32 arg1) {
    struct n64dk_r12 result;
    obj_t *actor;

    actor = *(obj_t **)((proc_t *)arg1)->unk_30;
    func_8000AD9C(arg1);
    result.w[1] = 1;
    result.w[0] = 0;
    if ((D_800B9954.button & 16 & 0xFFFF) != 0) {
        actor->unk_2C = actor->unk_2C - 0.25;
    }
    if ((D_800B9954.button & 32 & 0xFFFF) != 0) {
        actor->unk_2C = actor->unk_2C + 0.25;
    }
    return result;
}
