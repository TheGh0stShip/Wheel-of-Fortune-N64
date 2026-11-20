#include "wof.h"

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[0x14];
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ void (*callback)(s32);
} Item;

typedef struct {
    /* 0x00 */ u8 unk_00[0x4];
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 index;
    /* 0x0C */ s32 unk_0C;
} Cursor;

typedef struct {
    /* 0x00 */ u8 unk_00[0x30];
    /* 0x30 */ Cursor *cursor;
} Menu;

void func_800229D0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_80002CE0(44);
    func_80022784(arg0, arg1, (s32)&((Item *)arg2)[((Menu *)arg0)->cursor->index], 0);
    ((Item *)arg2)[((Menu *)arg0)->cursor->index].unk_18 = ((Menu *)arg0)->cursor->unk_04;
    do {
        ((Menu *)arg0)->cursor->index--;
        if (((Menu *)arg0)->cursor->index < 0) {
            ((Menu *)arg0)->cursor->index = arg3 - 1;
        }
    } while (((Item *)arg2)[((Menu *)arg0)->cursor->index].unk_00 == 0);
    ((Menu *)arg0)->cursor->unk_04 = ((Item *)arg2)[((Menu *)arg0)->cursor->index].unk_18;
    if (((Item *)arg2)[((Menu *)arg0)->cursor->index].callback != 0) {
        ((Item *)arg2)[((Menu *)arg0)->cursor->index].callback(((Menu *)arg0)->cursor->index);
    }
    func_80022784(arg0, arg1, (s32)&((Item *)arg2)[((Menu *)arg0)->cursor->index], 1);
    ((Menu *)arg0)->cursor->unk_0C = 15;
}
