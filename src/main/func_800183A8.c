#include "wof.h"
#include "func_800051B4.h"

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 player;
    /* 0x08 */ u8 unk_08[0x4];
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ s8 unk_10;
} State;

typedef struct {
    /* 0x00 */ u8 unk_00[0x30];
    /* 0x30 */ State *unk_30;
} Obj;

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[0xE4];
    /* 0xE8 */ s32 unk_E8;
    /* 0xEC */ u8 unk_EC[0x28];
} Player;

extern Player D_800B99A4[];
extern f32 D_80000F7C;
extern f64 D_80000F80;
extern f64 D_80000F88;
extern u8 D_800B61B5;
extern s32 D_800B96A0;
extern s32 D_800B96B4;
extern f32 D_800BCCF0;
extern s32 D_800FB808;

struct n64dk_r12 func_800183A8(s32 arg1) {
    struct n64dk_r12 result;
    Obj *obj;
    s32 node;
    s32 event;

    result.w[1] = 1;
    result.w[0] = 0;
    if (((Obj *)arg1)->unk_30->player != D_800FB808) {
        func_8000AD9C(arg1);
        return result;
    }
    while ((event = func_8000ACE8(arg1)) != 0) {
        switch (event) {
        case 8:
            func_80017C00(0, 0);
            obj = (Obj *)func_8000A56C((s32)func_8000EF68, 0x4000000);
            result.w[1] = 2;
            result.w[0] = 29;
            return result;
        case 29:
            func_80017C00(0, 0);
            obj = (Obj *)func_8000A56C((s32)func_8000FDFC, 0x4030000);
            node = func_8000B5DC(0x4010000, 0xFFFF0000);
            obj->unk_30->unk_00 = node;
            if (D_800BCCF0 > D_80000F7C) {
                obj->unk_30->unk_0C = D_800BCCF0 + func_8003CE58() % 10;
            } else {
                obj->unk_30->unk_0C = (f32)(func_8003CE58() % 10 + 50) + D_800BCCF0;
            }
            if (obj->unk_30->unk_0C > D_80000F80) {
                func_8000AAB0(arg1, 7, 0);
                result.w[1] = 1;
                result.w[0] = 40 / D_800B96B4;
                return result;
            } else {
                result.w[1] = 2;
                result.w[0] = -1;
                return result;
            }
            break;
        case 7:
            obj = (Obj *)func_8000A990(0x4030000, -1);
            if (obj->unk_30->unk_0C >= D_80000F88) {
                if (func_8003CE58() % 100 >= 51) {
                    func_80017C00(11, 0);
                } else {
                    func_80017C00(15, 1);
                }
            } else {
                func_80017C00(3, 0);
            }
            result.w[1] = 2;
            result.w[0] = 4;
            break;
        case 4:
            func_80017C00(0, 0);
            result.w[1] = 2;
            result.w[0] = 2;
            break;
        case 2:
            node = func_8000B5DC(0x4010000, 0xFFFF0000);
            func_80009364(0);
            if (func_8000928C() == -2 || func_8000928C() == -1) {
                func_80017C00(0, 0);
                func_80032B80();
                func_800051B4(D_800B99A4[D_800FB808].unk_00, 30, 0.8f);
                if (func_80017728() != 0) {
                    if (func_8000928C() == -2) {
                        func_80021B04(12, 16);
                        result.w[1] = 2;
                        result.w[0] = 16;
                        return result;
                    } else {
                        if (func_80033150(1, 16, D_800FB808) != 0) {
                            result.w[1] = 2;
                            result.w[0] = 16;
                        } else {
                            func_80017548();
                            func_8000A850(3);
                            result.w[1] = 0;
                        }
                        return result;
                    }
                }
                func_80017548();
                result.w[1] = 0;
                result.w[0] = 0;
                return result;
            }
            func_80017C00(3, 0);
            func_80032B10();
            func_8002EB40();
            result.w[1] = 2;
            result.w[0] = 5;
            break;
        case 16:
            func_80017548();
            func_8000A850(3);
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        case 5:
            func_80002CE0(D_800B99A4[D_800FB808].unk_E8 + (D_800B61B5 - 65));
            func_8000AAB0(arg1, 44, 0);
            result.w[1] = 1;
            result.w[0] = 30 / D_800B96B4;
            return result;
        case 44:
            func_8002A014();
            if (func_80007888(D_800B61B5, 0) > 0) {
                func_80007DAC(D_800B61B5);
                obj = (Obj *)func_8000A56C((s32)func_80010574, 0x1000000);
                obj->unk_30->unk_10 = D_800B61B5;
                result.w[1] = 2;
                result.w[0] = 6;
            } else {
                func_80002CE0(1);
                func_800051B4(D_800B99A4[D_800FB808].unk_00, 30, 0.8f);
                if (func_80017548() != 0) {
                    func_8000A850(3);
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
