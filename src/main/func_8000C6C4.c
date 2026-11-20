#include "wof.h"

struct n64dk_r12 { s32 w[3]; };

typedef struct {
    /* 0x00 */ u8 unk_00[0x10];
    /* 0x10 */ s16 x;
    /* 0x12 */ s16 y;
    /* 0x14 */ s16 z;
} Pos;

typedef struct {
    /* 0x00 */ Pos *pos;
    /* 0x04 */ u8 unk_04[0x4];
    /* 0x08 */ s32 unk_08;
} Data;

typedef struct {
    /* 0x00 */ u8 unk_00[0x30];
    /* 0x30 */ Data *data;
} Object;

typedef struct {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ u8 unk_04[0x8];
} Scale;

extern Scale D_80057810[];
extern s32 D_800BEE24;
s32 func_8000ACE8(s32 arg0);
s32 func_8003BEA8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_8003C2A8(s32, f32, f32, s32);
s32 func_80041018(s32 arg0, s32 arg1, s32 arg2);

struct n64dk_r12 func_8000C6C4(s32 arg1) {
    f32 mtx[4][4];
    f32 rot[4][4];
    struct n64dk_r12 ret;
    Pos *pos;
    s32 event;
    s32 index;

    pos = ((Object *)arg1)->data->pos;
    for (;;) {
        event = func_8000ACE8(arg1);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 34:
        case 36:
            ret.w[1] = 0;
            ret.w[0] = 1;
            return ret;
        }
    }
    index = ((Object *)arg1)->data->unk_08;
    func_8003C2A8((s32)mtx, (f32)D_800BEE24 * D_80057810[index].unk_00, (f32)D_800BEE24, 0);
    func_8003BEA8((s32)rot, 0xC275449C, 0x42698A3D, 0xC11D9168);
    func_80041018((s32)mtx, (s32)rot, (s32)mtx);
    pos->x = (s32)mtx[3][0];
    pos->y = (s32)mtx[3][1];
    pos->z = (s32)mtx[3][2];
    ret.w[1] = 1;
    ret.w[0] = 0;
    return ret;
}
