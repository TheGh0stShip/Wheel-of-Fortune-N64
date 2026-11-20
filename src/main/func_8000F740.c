#include "wof.h"


struct n64dk_r12 func_8000F740(proc_t *proc) {
    struct n64dk_r12 result;
    obj_t *actor;

    actor = proc->unk_30->obj;
    func_8000AD9C(proc);
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
