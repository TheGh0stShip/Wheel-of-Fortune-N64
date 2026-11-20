#include "wof.h"

typedef struct {
    /* 0x00 */ u8 unk_00[0x4];
    /* 0x04 */ s32 unk_04;
} Inner;

typedef struct {
    /* 0x00 */ u8 unk_00[0x30];
    /* 0x30 */ Inner *unk_30;
} Obj;

void func_8002D930();
s32 func_8000A56C(s32 arg0, s32 arg1);

void func_8002EB40(void) {
    Obj *obj;

    obj = (Obj *)func_8000A56C((s32)func_8002D930, 0x5010000);
    obj->unk_30->unk_04 = 6;
}
