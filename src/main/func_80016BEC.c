#include "wof.h"

struct n64dk_r12 func_80016BEC(s32 arg1) {
    struct n64dk_r12 result;
    s32 sp20;

    sp20 = *(s32 *)((proc_t *)arg1)->unk_30;
    func_8000AD9C(arg1);
    result.w[1] = 1;
    result.w[0] = 0;
    return result;
}
