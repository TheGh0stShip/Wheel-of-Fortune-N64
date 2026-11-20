#include "wof.h"

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[0x4];
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ u8 unk_10[0xE8];
    /* 0xF8 */ s32 unk_F8;
    /* 0xFC */ u8 unk_FC[0x18];
} Player;

extern s8 D_800B966A[];
extern Player D_800B9990[];
extern s8 D_8004B9FC[];
extern s8 D_800B9601[][21];

s32 func_80007888(register s32 arg0, s32 arg1) {
    u8 letter;
    s32 i;
    s32 count;
    s8 *p;

    letter = arg0;
    D_800B9CF8 = 1;
    D_800B9CFC = 1;
    D_800B9D00 = 1;
    switch (arg1) {
    case 0:
        p = (s8 *)func_800099B0((s32)D_8004BA04, letter);
        if (p == 0) {
            return -3;
        }
        break;
    case 1:
        p = (s8 *)func_800099B0((s32)D_8004B9FC, letter);
        if (p == 0) {
            return -2;
        }
        break;
    default:
        p = (s8 *)func_800099B0((s32)D_8004B9FC, letter);
        if (p != 0) {
            arg1 = 1;
        } else {
            arg1 = 0;
        }
        break;
    }
    p = (s8 *)func_800099B0((s32)D_800B966A, letter);
    if (p == 0) {
        return -1;
    }
    D_800B966A[p - D_800B966A] = 32;
    count = 0;
    for (i = 0; i < 4; i++) {
        p = D_800B9601[i];
        while (p != 0) {
            p = (s8 *)func_800099B0((s32)p, letter);
            if (p != 0) {
                count++;
                p++;
            }
        }
    }
    if (D_800BCA00 != 0) {
        if (arg1 == 0) {
            D_800B9990[D_800FB808].unk_00 += D_800B953C * count;
        }
        return count;
    }
    if (count > 0 && arg1 == 0) {
        if (func_8000928C() > 0) {
            if (func_8000928C() == 10000) {
                D_800B9990[D_800FB808].unk_F8 += 10000;
                D_800B9538 = 1;
                D_800B9990[D_800FB808].unk_0C = 1;
                func_80008F64();
            } else {
                D_800B9990[D_800FB808].unk_00 += func_8000928C() * count;
            }
            goto end;
        }
    }
    if (arg1 != 0) {
        D_800B9990[D_800FB808].unk_00 -= 250;
    } else if (count > 0) {
        if (arg1 == 0) {
            if (func_8000928C() < -4) {
                D_800B9990[D_800FB808].unk_08 = 1;
                func_80008F64();
            end:;
            }
        }
    }
    return count;
}
