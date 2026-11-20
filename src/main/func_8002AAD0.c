#include "wof.h"

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
        D_8005A998[((Cursor *)((proc_t *)arg0)->unk_30)->index].unk_1C = D_8005A998[((Cursor *)((proc_t *)arg0)->unk_30)->index].unk_14;
    } else {
        if (((Cursor *)((proc_t *)arg0)->unk_30)->index != 3) {
            ((Cursor *)((proc_t *)arg0)->unk_30)->index++;
            if (((Cursor *)((proc_t *)arg0)->unk_30)->index >= 3) {
                ((Cursor *)((proc_t *)arg0)->unk_30)->index = 0;
            }
        }
        D_8005A828[((Cursor *)((proc_t *)arg0)->unk_30)->index].unk_1C = D_8005A828[((Cursor *)((proc_t *)arg0)->unk_30)->index].unk_14;
    }
    D_800B61B5 = ((CursorBytes *)((proc_t *)arg0)->unk_30)->unk_07 + 65;
    ((Cursor *)((proc_t *)arg0)->unk_30)->unk_0C = 15;
}
