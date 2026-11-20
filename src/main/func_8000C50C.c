#include "wof.h"

typedef struct {
    /* 0x00 */ u8 unk_00[0x10];
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ s16 unk_14;
} Pos;

typedef struct {
    /* 0x00 */ Pos *unk_00;
    /* 0x04 */ u8 unk_04[0x4];
    /* 0x08 */ s32 unk_08;
} Data;

typedef struct {
    /* 0x00 */ u8 unk_00[0x30];
    /* 0x30 */ Data *unk_30;
} Obj;

struct n64dk_r12 func_8000C50C(s32 arg1) {
    s32 mtxA[12];
    f32 x;
    f32 y;
    f32 z;
    s32 mtxB[16];
    struct n64dk_r12 result;
    Pos *pos;
    s32 event;
    s8 pad0;

    pos = ((Obj *)arg1)->unk_30->unk_00;
    while ((event = func_8000ACE8(arg1)) != 0) {
        switch (event) {
        case 34:
        case 36:
            result.w[1] = 0;
            result.w[0] = 1;
            return result;
        }
    }
    func_8003C2A8(mtxA, 0, 0, D_800BEE24);
    func_8003BEA8(mtxB, 0, ((Obj *)arg1)->unk_30->unk_08 * 15, 0);
    func_80041018(mtxA, mtxB, mtxA);
    pos->unk_10 = x;
    pos->unk_12 = y;
    pos->unk_14 = z;
    result.w[1] = 1;
    result.w[0] = 0;
    return result;
}
