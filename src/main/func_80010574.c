#include "wof.h"

struct n64dk_r12 { s32 w[3]; };

typedef struct {
    /* 0x00 */ u8 unk_00[0x4];
    /* 0x04 */ s32 row;
    /* 0x08 */ s32 col;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ u8 letter;
} Data;

typedef struct {
    /* 0x00 */ u8 unk_00[0x30];
    /* 0x30 */ Data *data;
} Obj;

typedef struct {
    /* 0x00 */ s32 color;
    /* 0x04 */ u8 unk_04[0x18];
} Tile;

extern Tile D_800B9D20[];
extern Tile D_800B9E70[];
extern Tile D_800B9FF8[];
extern Tile D_800BA180[];
extern s32 D_800B61A8;
extern u8 D_800B9601[][21];
extern s32 D_800B96A8;
s32 func_80002CE0(s32 arg0);
void func_8000A850(s32 arg0);
s32 func_8000ACE8(s32 arg0);
void func_80032AD4(s32 arg0);

struct n64dk_r12 func_80010574(s32 arg1) {
    struct n64dk_r12 ret;
    s32 pad0[2];
    s32 row;
    s32 col;
    s32 startRow;
    u8 letter;
    s32 event;

    while ((event = func_8000ACE8(arg1)) != 0) {
        switch (event) {
        case 8:
            ((Obj *)arg1)->data->unk_0C = 0;
            ((Obj *)arg1)->data->row = 0;
            if (D_800B61A8 == 1) {
                ((Obj *)arg1)->data->col = 0;
            } else {
                ((Obj *)arg1)->data->col = 13;
            }
            D_800B96A8 = D_800B96A8 + 2;
            ret.w[1] = 1;
            ret.w[0] = 0;
            return ret;
            break;
        case 34:
            ret.w[1] = 0;
            ret.w[0] = 0;
            return ret;
        case 49:
            func_8000A850(6);
            ret.w[1] = 0;
            ret.w[0] = 0;
            return ret;
        }
    }
    letter = ((Obj *)arg1)->data->letter;
    col = ((Obj *)arg1)->data->col;
    startRow = ((Obj *)arg1)->data->row;
    if (((Obj *)arg1)->data->unk_0C == 0) {
        if (D_800B61A8 == 1) {
            if (col >= 7) {
                func_80032AD4(0);
                ((Obj *)arg1)->data->unk_0C = 1;
            }
        } else {
            if (col < 7) {
                func_80032AD4(0);
                ((Obj *)arg1)->data->unk_0C = 1;
            }
        }
    }
    while (col < 14 && col >= 0) {
        row = startRow;
        while (row < 4) {
            startRow = 0;
            if (letter == D_800B9601[row][col]) {
                ((Obj *)arg1)->data->row = row + 1;
                ((Obj *)arg1)->data->col = col;
                if (((Obj *)arg1)->data->row >= 4) {
                    ((Obj *)arg1)->data->row = 0;
                    ((Obj *)arg1)->data->col = col + D_800B61A8;
                }
                switch (row) {
                case 0:
                    D_800B9D20[col].color = 0x1111AAFF;
                    break;
                case 1:
                    D_800B9E70[col].color = 0x1111AAFF;
                    break;
                case 2:
                    D_800B9FF8[col].color = 0x1111AAFF;
                    break;
                case 3:
                    D_800BA180[col].color = 0x1111AAFF;
                    break;
                }
                func_80002CE0(2);
                ret.w[1] = 1;
                ret.w[0] = 15;
                return ret;
            }
            row++;
        }
        col = col + D_800B61A8;
    }
    if (((Obj *)arg1)->data->unk_0C == 0) {
        func_80032AD4(0);
        ((Obj *)arg1)->data->unk_0C = 1;
    }
    ret.w[1] = 2;
    ret.w[0] = 49;
    return ret;
}
