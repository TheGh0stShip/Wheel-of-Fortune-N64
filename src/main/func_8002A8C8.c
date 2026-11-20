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

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[0x4];
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ u8 unk_0C[0x1C];
} Entry;

extern Entry D_8005A83C[];
extern Entry D_8005A9AC[];

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
        D_8005A9AC[((Cursor *)((proc_t *)arg0)->unk_30)->unk_04.value].unk_08 = D_8005A9AC[((Cursor *)((proc_t *)arg0)->unk_30)->unk_04.value].unk_00;
    } else {
        if (((Cursor *)((proc_t *)arg0)->unk_30)->unk_04.value != 3) {
            ((Cursor *)((proc_t *)arg0)->unk_30)->unk_04.value--;
        }
        if (((Cursor *)((proc_t *)arg0)->unk_30)->unk_04.value < 0) {
            ((Cursor *)((proc_t *)arg0)->unk_30)->unk_04.value = 2;
        }
        D_8005A83C[((Cursor *)((proc_t *)arg0)->unk_30)->unk_04.value].unk_08 = D_8005A83C[((Cursor *)((proc_t *)arg0)->unk_30)->unk_04.value].unk_00;
    }
    D_800B61B5 = ((Cursor *)((proc_t *)arg0)->unk_30)->unk_04.bytes[3] + 65;
    ((Cursor *)((proc_t *)arg0)->unk_30)->unk_0C = 15;
}
