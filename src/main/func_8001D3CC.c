#include "wof.h"

typedef struct {
    /* 0x00 */ u8 unk_00[0x4];
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ u8 unk_08[0x4];
    /* 0x0C */ f32 unk_0C;
} Data;

typedef struct {
    /* 0x00 */ u8 unk_00[0x30];
    /* 0x30 */ Data *data;
} Obj;

void func_8001C584(s32);
extern f32 D_800B8298;
s32 func_8000A56C(s32 arg0, s32 arg1);

void func_8001D3CC(s32 arg0) {
    Obj *obj;
    s32 pad0;
    s8 pad1;

    obj = (Obj *)func_8000A56C((s32)func_8001C584, arg0 | 0x2030000);
    obj->data->unk_04 = arg0;
    obj->data->unk_0C = D_800B8298;
}
