#include "wof.h"

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ u8 unk_08[0x38];
    /* 0x40 */ s32 unk_40;
} Obj;

extern s32 D_800BEE50;

s32 func_8000A4A4(s32 arg0, s32 arg1) {
    Obj *prev;
    s32 next;

    prev = (Obj *)func_8000A158(arg0);
    if (prev == 0) {
        return 0;
    }
    next = ((Obj *)arg0)->unk_40;
    prev->unk_40 = next;
    D_800BEE50--;
    ((Obj *)arg0)->unk_00 = 0;
    func_8000A408(((Obj *)arg0)->unk_04);
    if (arg1 != 0) {
        func_8000B2D4(((Obj *)arg0)->unk_04);
    }
    return 1;
}
