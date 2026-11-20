#include "wof.h"

typedef struct {
    /* 0x00 */ u8 unk_00[0x10];
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ f32 unk_1C;
    /* 0x20 */ s32 unk_20;
} Data;

typedef struct {
    /* 0x00 */ u8 unk_00[0x30];
    /* 0x30 */ Data *unk_30;
} Obj;

extern f32 D_80001A74;
void func_80033CF8();
void func_80034028();
s32 func_8000A56C(s32 arg0, s32 arg1);
s32 func_80015848(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_8003CE58(void);

void func_800343F8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    s32 sp10;
    Obj *obj;

    obj = (Obj *)func_8000A56C((s32)func_80034028, 0x5030000);
    sp10 = func_80015848((s32)obj, 0, (s32)func_80033CF8, 0x5030000);
    obj->unk_30->unk_10 = func_8003CE58() % arg6 - arg7 + arg7;
    obj->unk_30->unk_1C = (f32)(func_8003CE58() % arg4 - arg5 + arg5) / D_80001A74;
    obj->unk_30->unk_20 = 0;
    obj->unk_30->unk_14 = func_8003CE58() % arg1 + arg0;
    obj->unk_30->unk_18 = func_8003CE58() % arg3 + arg2;
}
