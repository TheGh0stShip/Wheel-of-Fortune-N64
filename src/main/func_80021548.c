#include "wof.h"

typedef struct {
    /* 0x00 */ u8 unk_00[0x10];
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ s16 unk_12;
} Obj;

typedef struct {
    /* 0x00 */ Obj *unk_00;
    /* 0x04 */ u8 unk_04[0x1C];
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ s32 unk_24;
} State;

typedef struct {
    /* 0x00 */ u8 unk_00[0x30];
    /* 0x30 */ State *unk_30;
} Task;

extern s32 D_800B3CB8;
extern s32 D_800B40C4;
extern s32 D_800B8294;
extern s32 D_800BCA28;

struct n64dk_r12 func_80021548(s32 arg1) {
    s32 event;
    struct n64dk_r12 ret;
    s8 pad0;

    ret.w[1] = 1;
    ret.w[0] = 0;
    for (;;) {
        event = func_8000ACE8(arg1);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 8:
            if (((Task *)arg1)->unk_30->unk_24 > 0) {
                D_800B8294 = ((Task *)arg1)->unk_30->unk_24;
            }
            D_800B3CB8 = 4;
            break;
        case 34:
            ret.w[1] = 0;
            ret.w[0] = 1;
            return ret;
        }
    }
    func_800212C0(arg1);
    if (D_800B40C4 != 0) {
        func_8000B9FC(1);
        D_800B3CB8 = 0;
        ret.w[1] = 0;
        ret.w[0] = 1;
        if (D_800B40C4 == 2) {
            func_800A4E58(0);
            func_800219B8(D_800BCA28, ((Task *)arg1)->unk_30->unk_20, ((Task *)arg1)->unk_30->unk_00->unk_10, ((Task *)arg1)->unk_30->unk_00->unk_12);
        } else if (((Task *)arg1)->unk_30->unk_20 != 0) {
            func_8000A850(((Task *)arg1)->unk_30->unk_20);
        }
    }
    return ret;
}
