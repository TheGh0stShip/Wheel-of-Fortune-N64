#include "wof.h"

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ u8 unk_0C[0x1C];
} Key;

typedef struct {
    /* 0x00 */ u8 unk_00[0x4];
    /* 0x04 */ s32 index;
    /* 0x08 */ u8 unk_08[0x4];
    /* 0x0C */ s32 unk_0C;
} Cursor;

typedef struct {
    /* 0x00 */ u8 unk_00[0x7];
    /* 0x07 */ u8 unk_07;
} CursorBytes;

typedef struct {
    /* 0x00 */ u8 unk_00[0x30];
    /* 0x30 */ Cursor *cursor;
} Menu;

extern Key D_8005A83C[];
extern Key D_8005A9AC[];
extern s8 D_800B61B5;
extern s32 D_800BED88;
s32 func_80002CE0(s32 arg0);

void func_8002AAD0(s32 arg0, s32 arg1, s32 arg2) {
    D_800BED88++;
    if (arg2 != 0) {
        func_80002CE0(43);
    }
    if (arg1 != 0) {
        ((Menu *)arg0)->cursor->index++;
        if (((Menu *)arg0)->cursor->index == 13) {
            ((Menu *)arg0)->cursor->index = 0;
        }
        if (((Menu *)arg0)->cursor->index >= 26) {
            ((Menu *)arg0)->cursor->index = 13;
        }
        D_8005A9AC[((Menu *)arg0)->cursor->index].unk_08 = D_8005A9AC[((Menu *)arg0)->cursor->index].unk_00;
    } else {
        if (((Menu *)arg0)->cursor->index != 3) {
            ((Menu *)arg0)->cursor->index++;
            if (((Menu *)arg0)->cursor->index >= 3) {
                ((Menu *)arg0)->cursor->index = 0;
            }
        }
        D_8005A83C[((Menu *)arg0)->cursor->index].unk_08 = D_8005A83C[((Menu *)arg0)->cursor->index].unk_00;
    }
    D_800B61B5 = ((CursorBytes *)((Menu *)arg0)->cursor)->unk_07 + 65;
    ((Menu *)arg0)->cursor->unk_0C = 15;
}
