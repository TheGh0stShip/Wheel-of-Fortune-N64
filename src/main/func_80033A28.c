#include "wof.h"

typedef struct {
    /* 0x00 */ u8 unk_00[0x4];
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
} Data;

typedef struct {
    /* 0x00 */ u8 unk_00[0x30];
    /* 0x30 */ Data *unk_30;
} Obj;

extern s32 D_800B96A8;
extern s32 D_800B96B4;

struct n64dk_r12 func_80033A28(s32 arg1) {
    struct n64dk_r12 result;
    s32 event;
    s32 sp24;

    result.w[1] = 1;
    result.w[0] = 0;
    while ((event = func_8000ACE8(arg1)) != 0) {
        switch (event) {
        case 8:
            func_80002CE0(10);
            D_800B96A8 = 2;
            ((Obj *)arg1)->unk_30->unk_04 = 0;
            ((Obj *)arg1)->unk_30->unk_08 = 0;
            break;
        }
    }
    if (((Obj *)arg1)->unk_30->unk_04 > 0) {
        switch (((Obj *)arg1)->unk_30->unk_04) {
        case 1:
            sp24 = func_80002CE0(8);
            break;
        case 2:
            sp24 = func_80002CE0(9);
            break;
        case 3:
            sp24 = func_80002CE0(10);
            break;
        default:
            sp24 = func_80002CE0(func_8003CE58() % 3 + 16);
        }
        if (D_800B96A8 == ((Obj *)arg1)->unk_30->unk_04) {
            D_800B96A8 = 0;
            ((Obj *)arg1)->unk_30->unk_04 = 0;
        }
    }
    if (((Obj *)arg1)->unk_30->unk_04 < D_800B96A8) {
        ((Obj *)arg1)->unk_30->unk_04++;
        result.w[0] = 10 / D_800B96B4;
    }
    return result;
}
