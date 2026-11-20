#include "wof.h"

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ u8 unk_08[0x4];
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ s8 unk_10;
} State;


struct n64dk_r12 func_8001AE18(s32 arg1) {
    struct n64dk_r12 result;
    proc_t *obj;
    s32 target;
    s32 event;

    result.w[1] = 1;
    result.w[0] = 0;
    if (((State *)((proc_t *)arg1)->unk_30)->unk_04 != D_800FB808) {
        func_8000AD9C(arg1);
        return result;
    }
    for (;;) {
        event = func_8000ACE8(arg1);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 8:
            func_80017C00(0, 1);
            obj = func_8000A56C(func_8000FDFC, 0x4000000);
            target = func_8000B5DC(0x4010000, 0xFFFF0000);
            ((State *)obj->unk_30)->unk_00 = target;
            ((State *)obj->unk_30)->unk_0C = (f32)(guRandom() % 50 + 100);
            if ((f64)((State *)obj->unk_30)->unk_0C > 80.0) {
                func_8000AAB0(arg1, 7, 0);
                result.w[1] = 1;
                result.w[0] = 30 / D_800B96B4;
                return result;
            } else {
                result.w[1] = 2;
                result.w[0] = -1;
                return result;
            }
            break;
        case 7:
            if (func_80009C98(100) >= 76) {
                func_80017C00(15, 1);
            } else {
                func_80017C00(3, 1);
            }
            result.w[1] = 2;
            result.w[0] = 4;
            return result;
            break;
        case 4:
            func_80017C00(0, 1);
            result.w[1] = 2;
            result.w[0] = 2;
            return result;
            break;
        case 2:
            target = func_8000B5DC(0x4010000, 0xFFFF0000);
            func_80009364(0);
            if (func_8000928C() == -1) {
                func_80032B80();
                func_80017C00(0, 1);
                if (func_80017548() != 0) {
                    func_8000A850(3);
                    func_8000A850(24);
                }
                result.w[1] = 0;
                result.w[0] = 0;
                return result;
            } else {
                if (func_8000928C() == -2) {
                    func_80032B80();
                    func_80017C00(0, 1);
                    if (func_80017728() != 0) {
                        func_80021B04(12, 16);
                        result.w[1] = 2;
                        result.w[0] = 16;
                        return result;
                    }
                    func_80017548();
                    result.w[1] = 0;
                    result.w[0] = 0;
                    return result;
                }
            }
            func_80032B10();
            func_80017C00(3, 1);
            func_8002EB90(func_8001A894(((State *)((proc_t *)arg1)->unk_30)->unk_0C, arg1) & 255);
            func_8000AAB0(arg1, 5, 0);
            result.w[1] = 1;
            result.w[0] = 60 / D_800B96B4;
            return result;
        case 16:
            func_80017548();
            func_8000A850(3);
            func_8000A850(24);
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        case 5:
            func_80002CE0(D_800B9990[D_800FB808].unk_0FC + (D_800B61B5 - 65));
            func_8000AAB0(arg1, 44, 0);
            result.w[1] = 1;
            result.w[0] = 30 / D_800B96B4;
            return result;
        case 44:
            func_8002A014();
            obj = (proc_t *)func_8000A990(0x5010000, -1);
            func_8000AAB0((s32)obj, 23, 0);
            if (func_80007888(D_800B61B5, 0) > 0) {
                func_80007DAC(D_800B61B5);
                obj = func_8000A56C(func_80010574, 0x1000000);
                ((State *)obj->unk_30)->unk_10 = D_800B61B5;
                result.w[1] = 2;
                result.w[0] = 6;
                return result;
            } else {
                func_80002CE0(1);
                if (func_80017548() != 0) {
                    func_8000A850(3);
                    func_8000A850(24);
                }
                result.w[1] = 0;
                result.w[0] = 0;
                return result;
            }
            break;
        case 6:
            if (func_8000928C() == -3) {
                D_800B96A0 = 1;
            }
            func_8000A850(24);
            func_8000A850(3);
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        case 34:
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        }
    }
    return result;
}
