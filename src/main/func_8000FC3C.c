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
        obj->unk_2C = obj->unk_2C - ((Task *)arg1)->unk_30->unk_0C / 60.0f * D_800B96B4;
        ((Task *)arg1)->unk_30->unk_0C = ((Task *)arg1)->unk_30->unk_0C - D_800B96B4 * 0.5;
    }
    if (((Task *)arg1)->unk_30->unk_0C <= 50.0f) {
        if (((Task *)arg1)->unk_30->unk_10 > 50.0f) {
            func_8000A850(4);
        }
    }
    D_800BCCF0 = ((Task *)arg1)->unk_30->unk_0C;
    ((Task *)arg1)->unk_30->unk_10 = ((Task *)arg1)->unk_30->unk_0C;
    return ret;
}
