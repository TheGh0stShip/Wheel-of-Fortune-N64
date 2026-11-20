#include "wof.h"

typedef struct {
    /* 0x00 */ u8 unk_00[0x4];
    union {
        /* 0x04 */ s32 index;
        /* 0x04 */ u8 bytes[4];
    } unk_04;
} Info;

typedef struct {
    /* 0x00 */ u8 unk_00[0x30];
    /* 0x30 */ Info *unk_30;
} Obj;

extern s8 D_800B61B5;
extern u8 D_800B966A[];

void func_8002D8B0(s32 arg0) {
    if (D_800B966A[((Obj *)arg0)->unk_30->unk_04.index] == 32) {
        func_8002AAD0(arg0, 1, 0);
    }
    D_800B61B5 = ((Obj *)arg0)->unk_30->unk_04.bytes[3] + 65;
}
