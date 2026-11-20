#include "wof.h"


struct n64dk_r12 func_8002EFC0(proc_t *proc) {
    struct n64dk_r12 result;
    proc_t *obj;
    s32 node;
    s32 event;

    result.w[1] = 1;
    result.w[0] = 0;
    while ((event = func_8000ACE8(proc)) != 0) {
        switch (event) {
        case 8:
            func_8000AAB0(proc, 41, 0);
            result.w[1] = 1;
            result.w[0] = 180 / D_800B96B4;
            return result;
        case 41:
            func_80021B04(8, 44);
            result.w[1] = 2;
            result.w[0] = 44;
            return result;
        case 2:
            func_80009364(1);
            if (func_8000928C() <= 0 || func_8000928C() == 10000) {
                result.w[1] = 1;
                result.w[0] = 60 / D_800B96B4;
                return result;
            }
            func_8000A850(32);
            func_80009F98((s32)"Final spin is ");
            func_80009D78(func_8000928C());
            func_80009F98((s32)"\n");
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        }
    }
    func_80017C00(0, 1);
    obj = func_8000A56C(func_8000FDFC, 0x4000000);
    node = func_8000B5DC(0x4010000, 0xFFFF0000);
    obj->unk_30->data8002EFC0.unk_00 = node;
    obj->unk_30->data8002EFC0.unk_0C = guRandom() % 25 + 75;
    result.w[1] = 2;
    result.w[0] = 2;
    return result;
}
