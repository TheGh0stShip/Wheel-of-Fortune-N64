#include "wof.h"

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[0x14];
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ void (*callback)(s32);
} Item;

typedef struct {
    /* 0x00 */ u8 unk_00[0x4];
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 index;
    /* 0x0C */ s32 unk_0C;
} Cursor;

void func_800229D0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_80002CE0(44);
    func_80022784(arg0, arg1, (s32)&((Item *)arg2)[((Cursor *)((proc_t *)arg0)->unk_30)->index], 0);
    ((Item *)arg2)[((Cursor *)((proc_t *)arg0)->unk_30)->index].unk_18 = ((Cursor *)((proc_t *)arg0)->unk_30)->unk_04;
    do {
        ((Cursor *)((proc_t *)arg0)->unk_30)->index--;
        if (((Cursor *)((proc_t *)arg0)->unk_30)->index < 0) {
            ((Cursor *)((proc_t *)arg0)->unk_30)->index = arg3 - 1;
        }
    } while (((Item *)arg2)[((Cursor *)((proc_t *)arg0)->unk_30)->index].unk_00 == 0);
    ((Cursor *)((proc_t *)arg0)->unk_30)->unk_04 = ((Item *)arg2)[((Cursor *)((proc_t *)arg0)->unk_30)->index].unk_18;
    if (((Item *)arg2)[((Cursor *)((proc_t *)arg0)->unk_30)->index].callback != 0) {
        ((Item *)arg2)[((Cursor *)((proc_t *)arg0)->unk_30)->index].callback(((Cursor *)((proc_t *)arg0)->unk_30)->index);
    }
    func_80022784(arg0, arg1, (s32)&((Item *)arg2)[((Cursor *)((proc_t *)arg0)->unk_30)->index], 1);
    ((Cursor *)((proc_t *)arg0)->unk_30)->unk_0C = 15;
}
