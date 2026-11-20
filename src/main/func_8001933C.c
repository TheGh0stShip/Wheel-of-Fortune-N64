#include "wof.h"
#include "func_800051B4.h"

typedef struct {
    /* 0x00 */ u8 unk_00[0x4];
    /* 0x04 */ s32 player;
} Data;

typedef struct {
    /* 0x00 */ u8 unk_00[0x30];
    /* 0x30 */ Data *data;
} Obj;

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[0x110];
} Player;

extern Player D_800B99A4[];
extern s32 D_800B96A8;
extern s32 D_800BCA00;
extern s32 D_800FB808;

struct n64dk_r12 func_8001933C(s32 arg1) {
    struct n64dk_r12 ret;
    s32 task;
    s32 pad0;
    s32 event;

    ret.w[1] = 1;
    ret.w[0] = 0;
    if (((Obj *)arg1)->data->player != D_800FB808) {
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
                func_800051B4(D_800B99A4[D_800FB808].unk_00, 30, 0.8f);
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
