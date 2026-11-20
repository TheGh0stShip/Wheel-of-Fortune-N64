#include "wof.h"

struct n64dk_r12 func_80016BEC(proc_t *proc) {
    struct n64dk_r12 result;
    obj_t *sp20;

    sp20 = proc->unk_30->obj;
    func_8000AD9C(proc);
    result.w[1] = 1;
    result.w[0] = 0;
    return result;
}
