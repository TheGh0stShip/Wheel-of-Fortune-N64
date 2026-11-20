#include "wof.h"
#include "func_800051B4.h"


struct n64dk_r12 func_8001933C(s32 arg1) {
    struct n64dk_r12 ret;
    s32 task;
    s32 unused;  /* NOTE: unused in the original */
    s32 event;

    ret.w[1] = 1;
    ret.w[0] = 0;
    if (((data8001933C_t *)((proc_t *)arg1)->unk_30)->player != D_800FB808) {
        func_8000AD9C(arg1);
        return ret;
    }
    task = func_8000A990(0x1020000, -1);
    while ((event = func_8000ACE8(arg1)) != 0) {
        switch (event) {
        case 8:
            func_8002EBF4();
            func_80017C00(3, 0);
            ret.w[1] = 2;
            ret.w[0] = 5;
            return ret;
        case 5:
            if (func_800088E4() == 1) {
                D_800B96A8 = D_800B96A8 + 2;
                func_8000AAB0(task, 19, 0);
                func_8000A850(10);
                ret.w[1] = 0;
                ret.w[0] = 0;
            } else {
                func_8000AAB0(task, 20, 0);
                func_80002CE0(1);
                func_800051B4(D_800B9990[D_800FB808].unk_014, 30, 0.8f);
                if (D_800BCA00 == 0) {
                    if (func_80017548() != 0) {
                        func_8000A850(10);
                    }
                } else {
                    func_8000A850(10);
                }
                ret.w[1] = 0;
                ret.w[0] = 0;
                return ret;
            }
            break;
        case 34:
            ret.w[1] = 0;
            ret.w[0] = 0;
            return ret;
        }
    }
    return ret;
}
