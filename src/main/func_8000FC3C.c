#include "wof.h"

typedef struct {
    /* 0x00 */ u8 unk_00[0x2C];
    /* 0x2C */ f32 unk_2C;
} Obj;

typedef struct {
    /* 0x00 */ Obj *unk_00;
    /* 0x04 */ u8 unk_04[0x8];
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
} State;

typedef struct {
    /* 0x00 */ u8 unk_00[0x30];
    /* 0x30 */ State *unk_30;
} Task;

extern f32 D_80000BEC;
extern f64 D_80000BF0;
extern f32 D_80000BF8;
extern f32 D_80000BFC;
extern f32 D_800BCCF0;

struct n64dk_r12 func_8000FC3C(s32 arg1) {
    struct n64dk_r12 ret;
    Obj *obj;

    obj = ((Task *)arg1)->unk_30->unk_00;
    ret.w[1] = 1;
    ret.w[0] = 0;
    if (((Task *)arg1)->unk_30->unk_0C <= 0.0f) {
        func_8000A56C((s32)func_8000F84C, 0x4000000);
        ret.w[1] = 0;
        ret.w[0] = 0;
    } else {
        obj->unk_2C = obj->unk_2C - ((Task *)arg1)->unk_30->unk_0C / D_80000BEC * D_800B96B4;
        ((Task *)arg1)->unk_30->unk_0C = ((Task *)arg1)->unk_30->unk_0C - D_800B96B4 * D_80000BF0;
    }
    if (((Task *)arg1)->unk_30->unk_0C <= D_80000BF8) {
        if (((Task *)arg1)->unk_30->unk_10 > D_80000BFC) {
            func_8000A850(4);
        }
    }
    D_800BCCF0 = ((Task *)arg1)->unk_30->unk_0C;
    ((Task *)arg1)->unk_30->unk_10 = ((Task *)arg1)->unk_30->unk_0C;
    return ret;
}
