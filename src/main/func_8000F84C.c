#include "wof.h"

struct n64dk_r12 func_8000F84C(s32 arg1) {
    struct n64dk_r12 ret;
    s32 sp20;
    s32 event;
    s8 pad0;

    sp20 = ((data8000F84C_t *)((proc_t *)arg1)->unk_30)->unk_00;
    ret.w[1] = 1;
    ret.w[0] = 0;
    while ((event = func_8000ACE8(arg1)) != 0) {
        switch (event) {
        case 8:
            func_80032858();
            func_80032B80();
            switch (func_8000928C()) {
            case -1:
                func_80002CE0(0);
                break;
            case -2:
                func_80002CE0(1);
                break;
            case 2500:
                D_800B96A8++;
                break;
            case 3500:
                ((data8000F84C_t *)((proc_t *)arg1)->unk_30)->unk_04 = 1;
                D_800B96A8++;
                func_8000AAB0(arg1, 41, 0);
                ret.w[1] = 1;
                ret.w[0] = 10 / D_800B96B4;
                return ret;
            case 5000:
                D_800B96A8++;
                func_8000AAB0(arg1, 41, 0);
                ret.w[1] = 1;
                ret.w[0] = 10 / D_800B96B4;
                return ret;
            case 10000:
                D_800B96A8 = D_800B96A8 + 3;
                func_8000AAB0(arg1, 41, 0);
                ret.w[1] = 1;
                ret.w[0] = 10 / D_800B96B4;
                return ret;
            }
            ret.w[1] = 1;
            ret.w[0] = 60 / D_800B96B4;
            return ret;
        }
    }
    ret.w[1] = 0;
    ret.w[0] = 0;
    func_8000A850(2);
    return ret;
}
