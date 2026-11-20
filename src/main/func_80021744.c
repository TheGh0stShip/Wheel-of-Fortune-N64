#include "wof.h"

struct n64dk_r12 { s32 w[3]; };

typedef struct {
    /* 0x00 */ u8 unk_00[0x10];
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ u8 unk_14[0xC];
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ s32 unk_24;
} Data;

typedef struct {
    /* 0x00 */ u8 unk_00[0x30];
    /* 0x30 */ Data *unk_30;
} Obj;

extern s32 D_800B3CB8;
extern s32 D_800B40C4;
extern s32 D_800B8294;
extern s32 D_800B96A4;
void func_8000A850(s32 arg0);
s32 func_8000ACE8(s32 arg0);
void func_8000B9FC(s32 arg0);
void func_80017C00(s32 arg0, s32 arg1);
void func_800213CC(s32 arg0);
void func_800325D0(s32 arg0, s32 arg1);

struct n64dk_r12 func_80021744(s32 arg1) {
    s32 event;
    struct n64dk_r12 result;
    s8 pad0;

    result.w[1] = 1;
    result.w[0] = 0;
    while ((event = func_8000ACE8(arg1)) != 0) {
        switch (event) {
        case 8:
            if (((Obj *)arg1)->unk_30->unk_24 > 0) {
                D_800B8294 = ((Obj *)arg1)->unk_30->unk_24;
            }
            D_800B3CB8 = 8;
            break;
        case 34:
            result.w[1] = 0;
            result.w[0] = 1;
            return result;
        }
    }
    func_800213CC(arg1);
    if (D_800B40C4 != 0) {
        func_80017C00(3, 0);
        D_800B96A4 = 0;
        func_8000B9FC(1);
        D_800B3CB8 = 0;
        result.w[1] = 0;
        result.w[0] = 1;
        func_800325D0(1, ((Obj *)arg1)->unk_30->unk_10);
        if (((Obj *)arg1)->unk_30->unk_20 != 0) {
            func_8000A850(((Obj *)arg1)->unk_30->unk_20);
        }
    }
    return result;
}
