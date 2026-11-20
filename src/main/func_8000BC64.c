#include "wof.h"

struct n64dk_r12 func_8000BC64(proc_t *proc) {
    struct n64dk_r12 result;
    s32 sp20;
    s32 event;

    sp20 = proc->unk_30->obj;
    result.w[1] = 1;
    result.w[0] = 0;
    while ((event = func_8000ACE8(proc)) != 0) {
        switch (event) {
        case 8:
            func_8000315C();
            func_8000AAB0(proc, 36, 0);
            result.w[1] = 1;
            result.w[0] = 2;
            return result;
        case 36:
            func_8000ADEC(proc);
            func_8000AF00();
            func_8000B9FC(1);
            func_8000BBA8();
            func_80016B9C(12);
            result.w[1] = 2;
            result.w[0] = 45;
            return result;
        case 45:
            func_80016B9C(3);
            func_800219B8(5, 40, 180, 20);
            result.w[1] = 0;
            result.w[0] = 1;
            return result;
        }
    }
    return result;
}
