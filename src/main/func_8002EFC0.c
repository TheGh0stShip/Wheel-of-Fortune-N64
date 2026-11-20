#include "wof.h"

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[0x8];
    /* 0x0C */ f32 unk_0C;
} Actor;

typedef struct {
    /* 0x00 */ u8 unk_00[0x30];
    /* 0x30 */ Actor *unk_30;
} Obj;

extern s32 D_8000190C;
extern s32 D_8000191C;
extern s32 D_800B96B4;

struct n64dk_r12 func_8002EFC0(s32 arg1) {
    struct n64dk_r12 result;
    Obj *obj;
    s32 node;
    s32 event;

    result.w[1] = 1;
    result.w[0] = 0;
    while ((event = func_8000ACE8(arg1)) != 0) {
        switch (event) {
        case 8:
            func_8000AAB0(arg1, 41, 0);
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
            func_80009F98((s32)&D_8000190C);
            func_80009D78(func_8000928C());
            func_80009F98((s32)&D_8000191C);
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        }
    }
    func_80017C00(0, 1);
    obj = (Obj *)func_8000A56C((s32)func_8000FDFC, 0x4000000);
    node = func_8000B5DC(0x4010000, 0xFFFF0000);
    obj->unk_30->unk_00 = node;
    obj->unk_30->unk_0C = func_8003CE58() % 25 + 75;
    result.w[1] = 2;
    result.w[0] = 2;
    return result;
}
