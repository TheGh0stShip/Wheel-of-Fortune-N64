#include "wof.h"


s32 func_80007888(register s32 arg0, s32 arg1) {
    u8 letter;
    s32 i;
    s32 count;
    u8 *p;

    letter = arg0;
    D_800B9CF8 = 1;
    D_800B9CFC = 1;
    D_800B9D00 = 1;
    switch (arg1) {
    case 0:
        p = (u8 *)func_800099B0((s32)D_8004BA04, letter);
        if (p == 0) {
            return -3;
        }
        break;
    case 1:
        p = (u8 *)func_800099B0((s32)D_8004B9FC, letter);
        if (p == 0) {
            return -2;
        }
        break;
    default:
        p = (u8 *)func_800099B0((s32)D_8004B9FC, letter);
        if (p != 0) {
            arg1 = 1;
        } else {
            arg1 = 0;
        }
        break;
    }
    p = (u8 *)func_800099B0((s32)D_800B966A, letter);
    if (p == 0) {
        return -1;
    }
    D_800B966A[p - D_800B966A] = 32;
    count = 0;
    for (i = 0; i < 4; i++) {
        p = D_800B9601[i];
        while (p != 0) {
            p = (u8 *)func_800099B0((s32)p, letter);
            if (p != 0) {
                count++;
                p++;
            }
        }
    }
    if (D_800BCA00 != 0) {
        if (arg1 == 0) {
            D_800B9990[D_800FB808].unk_000 += D_800B953C * count;
        }
        return count;
    }
    if (count > 0 && arg1 == 0) {
        if (func_8000928C() > 0) {
            if (func_8000928C() == 10000) {
                D_800B9990[D_800FB808].unk_0F8 += 10000;
                D_800B9538 = 1;
                D_800B9990[D_800FB808].unk_00C = 1;
                func_80008F64();
            } else {
                D_800B9990[D_800FB808].unk_000 += func_8000928C() * count;
            }
            goto end;
        }
    }
    if (arg1 != 0) {
        D_800B9990[D_800FB808].unk_000 -= 250;
    } else if (count > 0) {
        if (arg1 == 0) {
            if (func_8000928C() < -4) {
                D_800B9990[D_800FB808].unk_008 = 1;
                func_80008F64();
            end:;
            }
        }
    }
    return count;
}
