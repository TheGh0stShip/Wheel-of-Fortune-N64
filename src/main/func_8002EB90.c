#include "wof.h"

typedef struct {
    /* 0x00 */ u8 unk_00[0x4];
    /* 0x04 */ s32 unk_04;
} Inner;

typedef struct {
    /* 0x00 */ u8 unk_00[0x30];
    /* 0x30 */ Inner *unk_30;
} Obj;

void func_8002D930(void);
Obj *func_8000A56C(void (*arg0)(void), s32 arg1);

void func_8002EB90(register s32 arg0) {
    u8 sp10;
    Obj *obj;

    sp10 = arg0;
    obj = func_8000A56C(func_8002D930, 0x5010000);
    obj->unk_30->unk_04 = sp10 - 65;
}
