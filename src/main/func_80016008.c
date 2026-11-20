#include "wof.h"

typedef struct {
    /* 0x00 */ u8 unk_00[0x30];
    /* 0x30 */ s32 *unk_30;
} Obj;

void func_80016008(void) {
    Obj *obj;
    s32 sp14;

    sp14 = func_8000B5DC(0x1010000, -1);
    if (sp14 != 0) {
        obj = (Obj *)func_8000A990(0x1010000, -1);
        if (obj == 0) {
            obj = func_8000A56C(func_8000FFE0, 0x1010000);
            *obj->unk_30 = sp14;
        }
    }
}
