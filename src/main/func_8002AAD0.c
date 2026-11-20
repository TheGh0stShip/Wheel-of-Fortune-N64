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

extern Key D_8005A83C[];
extern Key D_8005A9AC[];

void func_8002AAD0(s32 arg0, s32 arg1, s32 arg2) {
    D_800BED88++;
    if (arg2 != 0) {
        func_80002CE0(43);
    }
    if (arg1 != 0) {
        ((Cursor *)((proc_t *)arg0)->unk_30)->index++;
        if (((Cursor *)((proc_t *)arg0)->unk_30)->index == 13) {
            ((Cursor *)((proc_t *)arg0)->unk_30)->index = 0;
        }
        if (((Cursor *)((proc_t *)arg0)->unk_30)->index >= 26) {
            ((Cursor *)((proc_t *)arg0)->unk_30)->index = 13;
        }
        D_8005A9AC[((Cursor *)((proc_t *)arg0)->unk_30)->index].unk_08 = D_8005A9AC[((Cursor *)((proc_t *)arg0)->unk_30)->index].unk_00;
    } else {
        if (((Cursor *)((proc_t *)arg0)->unk_30)->index != 3) {
            ((Cursor *)((proc_t *)arg0)->unk_30)->index++;
            if (((Cursor *)((proc_t *)arg0)->unk_30)->index >= 3) {
                ((Cursor *)((proc_t *)arg0)->unk_30)->index = 0;
            }
        }
        D_8005A83C[((Cursor *)((proc_t *)arg0)->unk_30)->index].unk_08 = D_8005A83C[((Cursor *)((proc_t *)arg0)->unk_30)->index].unk_00;
    }
    D_800B61B5 = ((CursorBytes *)((proc_t *)arg0)->unk_30)->unk_07 + 65;
    ((Cursor *)((proc_t *)arg0)->unk_30)->unk_0C = 15;
}
