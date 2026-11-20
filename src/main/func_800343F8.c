#include "wof.h"


void func_800343F8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    s32 sp10;
    proc_t *obj;

    obj = func_8000A56C(func_80034028, 0x5030000);
    sp10 = func_80015848((s32)obj, 0, func_80033CF8, 0x5030000);
    obj->unk_30->data80034028.count = guRandom() % arg6 - arg7 + arg7;
    obj->unk_30->data80034028.vx = (f32)(guRandom() % arg4 - arg5 + arg5) / 100.0f;
    obj->unk_30->data80034028.vy = 0;
    obj->unk_30->data80034028.x = guRandom() % arg1 + arg0;
    obj->unk_30->data80034028.y = guRandom() % arg3 + arg2;
}
