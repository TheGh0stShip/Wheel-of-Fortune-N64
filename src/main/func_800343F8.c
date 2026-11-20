#include "wof.h"

typedef struct {
    /* 0x00 */ u8 unk_00[0x10];
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ f32 unk_1C;
    /* 0x20 */ s32 unk_20;
} Data;


void func_800343F8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    s32 sp10;
    proc_t *obj;

    obj = (proc_t *)func_8000A56C((s32)func_80034028, 0x5030000);
    sp10 = func_80015848((s32)obj, 0, (s32)func_80033CF8, 0x5030000);
    ((Data *)obj->unk_30)->unk_10 = guRandom() % arg6 - arg7 + arg7;
    ((Data *)obj->unk_30)->unk_1C = (f32)(guRandom() % arg4 - arg5 + arg5) / 100.0f;
    ((Data *)obj->unk_30)->unk_20 = 0;
    ((Data *)obj->unk_30)->unk_14 = guRandom() % arg1 + arg0;
    ((Data *)obj->unk_30)->unk_18 = guRandom() % arg3 + arg2;
}
