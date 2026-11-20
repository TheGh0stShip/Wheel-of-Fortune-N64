#include "wof.h"

typedef struct {
    /* 0x00 */ u8 unk_00[0x4];
    /* 0x04 */ s32 row;
    /* 0x08 */ s32 col;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ u8 letter;
} Data;

typedef struct {
    /* 0x00 */ s32 color;
    /* 0x04 */ u8 unk_04[0x18];
} Tile;

extern Tile D_800B9D20[];
extern Tile D_800B9E70[];
extern Tile D_800B9FF8[];
extern Tile D_800BA180[];
extern u8 D_800B9601[][21];

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
            ((Data *)((proc_t *)arg1)->unk_30)->unk_0C = 0;
            ((Data *)((proc_t *)arg1)->unk_30)->row = 0;
            if (D_800B61A8 == 1) {
                ((Data *)((proc_t *)arg1)->unk_30)->col = 0;
            } else {
                ((Data *)((proc_t *)arg1)->unk_30)->col = 13;
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
    letter = ((Data *)((proc_t *)arg1)->unk_30)->letter;
    col = ((Data *)((proc_t *)arg1)->unk_30)->col;
    startRow = ((Data *)((proc_t *)arg1)->unk_30)->row;
    if (((Data *)((proc_t *)arg1)->unk_30)->unk_0C == 0) {
        if (D_800B61A8 == 1) {
            if (col >= 7) {
                func_80032AD4(0);
                ((Data *)((proc_t *)arg1)->unk_30)->unk_0C = 1;
            }
        } else {
            if (col < 7) {
                func_80032AD4(0);
                ((Data *)((proc_t *)arg1)->unk_30)->unk_0C = 1;
            }
        }
    }
    while (col < 14 && col >= 0) {
        row = startRow;
        while (row < 4) {
            startRow = 0;
            if (letter == D_800B9601[row][col]) {
                ((Data *)((proc_t *)arg1)->unk_30)->row = row + 1;
                ((Data *)((proc_t *)arg1)->unk_30)->col = col;
                if (((Data *)((proc_t *)arg1)->unk_30)->row >= 4) {
                    ((Data *)((proc_t *)arg1)->unk_30)->row = 0;
                    ((Data *)((proc_t *)arg1)->unk_30)->col = col + D_800B61A8;
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
    if (((Data *)((proc_t *)arg1)->unk_30)->unk_0C == 0) {
        func_80032AD4(0);
        ((Data *)((proc_t *)arg1)->unk_30)->unk_0C = 1;
    }
    ret.w[1] = 2;
    ret.w[0] = 49;
    return ret;
}
