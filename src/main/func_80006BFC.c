#include "wof.h"

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[0x8];
} EntryA;

typedef struct {
    /* 0x00 */ s32 base;
    /* 0x04 */ s32 range;
} Range;

extern EntryA D_8004BBA0[];
extern Range D_B025D810[];

void func_80006BFC(void) {
    s32 i;
    s32 kind;

    D_800BEE54 = 0;
    if (D_800BCD54 == 3) {
        D_800B619C = 2;
    }
    if (D_800B619C == 2) {
        D_800B9540 = 5000;
    } else {
        D_800B9540 = 0;
    }
    D_800B9980 = 0;
    if (D_800B619C != 6) {
        func_80008AB8();
    }
    switch (D_800B619C) {
    case 1:
    case 2:
        kind = 2;
        break;
    case 6:
        kind = 0;
        break;
    default:
        kind = 1;
    }
    i = D_B025D810[kind].base + func_80009C98(D_B025D810[kind].range);
    if (D_800BCD54 != 3) {
        while (D_8004BBA0[i].unk_00 != 0) {
            i = D_B025D810[kind].base + func_80009C98(D_B025D810[kind].range);
        }
    }
    func_80006E54(i, 0);
    D_800B9CF8 = D_800B619C < 6;
    D_800B9CFC = 0;
    D_800B9D00 = 0;
    for (i = 0; i < 3; i++) {
        D_800B9990[i].unk_010 = 0;
    }
}
