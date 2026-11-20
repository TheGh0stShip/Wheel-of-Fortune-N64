#include "wof.h"

typedef struct {
    /* 0x00 */ u8 unk_00[0x4];
    /* 0x04 */ union {
        s32 value;
        u8 bytes[4];
    } unk_04;
    /* 0x08 */ u8 unk_08[0x4];
    /* 0x0C */ s32 unk_0C;
} Cursor;


void func_8002A8C8(s32 arg0, s32 arg1) {
    D_800BED88++;
    func_80002CE0(43);
    if (arg1 != 0) {
        ((Cursor *)((proc_t *)arg0)->unk_30)->unk_04.value--;
        if (((Cursor *)((proc_t *)arg0)->unk_30)->unk_04.value == 12) {
            ((Cursor *)((proc_t *)arg0)->unk_30)->unk_04.value = 25;
        }
        if (((Cursor *)((proc_t *)arg0)->unk_30)->unk_04.value < 0) {
            ((Cursor *)((proc_t *)arg0)->unk_30)->unk_04.value = 12;
        }
        D_8005A998[((Cursor *)((proc_t *)arg0)->unk_30)->unk_04.value].unk_1C = D_8005A998[((Cursor *)((proc_t *)arg0)->unk_30)->unk_04.value].unk_14;
    } else {
        if (((Cursor *)((proc_t *)arg0)->unk_30)->unk_04.value != 3) {
            ((Cursor *)((proc_t *)arg0)->unk_30)->unk_04.value--;
        }
        if (((Cursor *)((proc_t *)arg0)->unk_30)->unk_04.value < 0) {
            ((Cursor *)((proc_t *)arg0)->unk_30)->unk_04.value = 2;
        }
        D_8005A828[((Cursor *)((proc_t *)arg0)->unk_30)->unk_04.value].unk_1C = D_8005A828[((Cursor *)((proc_t *)arg0)->unk_30)->unk_04.value].unk_14;
    }
    D_800B61B5 = ((Cursor *)((proc_t *)arg0)->unk_30)->unk_04.bytes[3] + 65;
    ((Cursor *)((proc_t *)arg0)->unk_30)->unk_0C = 15;
}
