#include "wof.h"

typedef struct {
    /* 0x00 */ u8 unk_00[0x2C];
    /* 0x2C */ f32 unk_2C;
} Obj;

typedef struct {
    /* 0x00 */ u8 unk_00[0xC];
    /* 0x0C */ f32 unk_0C;
} State;

typedef struct {
    /* 0x00 */ u8 unk_00[0x30];
    /* 0x30 */ State *unk_30;
} Task;

extern f32 D_80000BA4;
extern f32 D_80000BA8;
extern f32 D_80000BAC;
extern f32 D_80000BB0;
extern f32 D_800BCCF0;

struct n64dk_r12 func_8000EF68(s32 arg1) {
    struct n64dk_r12 ret;
    s32 pad0;
    Obj *obj;
    f32 delta;
    s32 pad1;
    s32 pad2;
    s32 event;

    ret.w[1] = 1;
    ret.w[0] = 0;
    obj = (Obj *)func_8000B5DC(0x4010000, 0xFFFF0000);
    if (obj == 0) {
        return ret;
    }
    for (;;) {
        event = func_8000ACE8(arg1);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 8:
            ((Task *)arg1)->unk_30->unk_0C = obj->unk_2C;
            break;
        case 34:
            ret.w[1] = 0;
            ret.w[0] = 0;
            return ret;
        }
    }
    delta = ((Task *)arg1)->unk_30->unk_0C - D_800B9956 / D_80057F44;
    if (delta > 0.0f) {
        delta = delta * D_80000BA4;
    }
    delta = delta - obj->unk_2C;
    delta = delta / (f32)(12 / D_800B96B4);
    D_800BCCF0 = delta * D_80000BA8 * D_80000BAC;
    obj->unk_2C = obj->unk_2C + delta;
    if ((D_800B96B0 & 0xA000 & 0xFFFF) != 0) {
        D_800BCCF0 = (f32)(func_8003CE58() % 40) + D_80000BB0;
        func_8000A850(29);
        ret.w[1] = 0;
        ret.w[0] = 0;
    }
    if (D_80057F48 < D_800BCCF0) {
        func_8000A850(29);
        ret.w[1] = 0;
        ret.w[0] = 0;
    }
    return ret;
}
