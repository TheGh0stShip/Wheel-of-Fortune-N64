#include "wof.h"

struct n64dk_r12 { s32 w[3]; };

typedef struct {
    /* 0x00 */ u8 unk_00[0x4];
    /* 0x04 */ s32 unk_04;
} Ref;

typedef struct {
    /* 0x00 */ u8 unk_00[0x28];
    /* 0x28 */ f32 unk_28;
    /* 0x2C */ f32 unk_2C;
    /* 0x30 */ Ref *unk_30;
} Task;

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
} Vec2f;

extern Vec2f D_800B39A0[];
extern f64 D_80000EAC;
extern f64 D_80000EB4;
extern f64 D_80000EBC;
extern f64 D_80000EC4;
extern f32 D_80057F7C;
extern f32 D_80057F80;
extern u16 D_800B9954;
extern s32 D_800FB808;
s32 func_8000B5DC(s32 arg0, s32 arg1);

struct n64dk_r12 func_80017938(s32 arg1) {
    struct n64dk_r12 sp10;
    s32 pad0;
    Task *task;

    sp10.w[1] = 1;
    sp10.w[0] = 0;
    if (((Task *)arg1)->unk_30->unk_04 != D_800FB808) {
        return sp10;
    }
    if ((D_800B9954 & 1 & 0xFFFF) != 0) {
        D_800B39A0[D_800FB808].y = D_800B39A0[D_800FB808].y - D_80000EAC;
    }
    if ((D_800B9954 & 2 & 0xFFFF) != 0) {
        D_800B39A0[D_800FB808].y = D_800B39A0[D_800FB808].y + D_80000EB4;
    }
    if ((D_800B9954 & 4 & 0xFFFF) != 0) {
        D_800B39A0[D_800FB808].x = D_800B39A0[D_800FB808].x - D_80000EBC;
    }
    if ((D_800B9954 & 8 & 0xFFFF) != 0) {
        D_800B39A0[D_800FB808].x = D_800B39A0[D_800FB808].x + D_80000EC4;
    }
    task = (Task *)func_8000B5DC(0x3000000, 0xFF000000);
    task->unk_28 = D_80057F7C + D_800B39A0[D_800FB808].x;
    task->unk_2C = D_80057F80 + D_800B39A0[D_800FB808].y;
    return sp10;
}
