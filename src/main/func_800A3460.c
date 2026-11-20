#include "wof.h"

typedef struct {
    /* 0x000 */ u8 unk_000[0x204];
    /* 0x204 */ s32 unk_204;
    /* 0x208 */ s32 unk_208;
    /* 0x20C */ u8 unk_20C[0x8];
    /* 0x214 */ s32 unk_214;
} Stream;

s32 func_800A3808(s32 arg0, s32 arg1);
s32 func_800A38F8(s32 arg0);
s32 func_800A3A3C(s32 arg0, s32 arg1, s32 arg2);
s32 func_800A3B40(s32 arg0);
s32 func_800A3E00(s32 arg0, s32 arg1);

s32 func_800A3460(s32 arg0, s32 arg1) {
    s32 sp10;
    s32 sp14;
    s32 sp18;
    s32 sp1C;
    s32 code;
    s32 err;
    s32 result;
    u8 low;
    s32 sp30[2];
    s32 sp38;
    s32 handled;

    sp10 = arg0 + 492;
    sp14 = arg0 + 496;
    sp18 = arg0 + 488;
    sp1C = arg0 + 484;
    if (arg1 == 0) {
        err = func_800A3808((s32)&code, arg0);
        if (((Stream *)arg0)->unk_204 != 0) {
            return 0;
        }
        if (err != 0) {
            return 0;
        }
    } else {
        err = 0;
        code = arg1;
    }
    while (1) {
        handled = 0;
        if (code == 442) {
            handled = 1;
            err = func_800A3A3C((s32)sp30, (s32)&sp38, arg0);
            if (err != 0) {
                return 0;
            }
            err = func_800A3808((s32)&code, arg0);
            if (err != 0) {
                return 0;
            }
        }
        if (code == 443) {
            handled = 1;
            err = func_800A3B40(arg0);
            if (err != 0) {
                return 0;
            }
            err = func_800A3808((s32)&code, arg0);
            if (err != 0) {
                return 0;
            }
        }
        low = code;
        while ((code & -256) == 256 && (u32)low >= 188) {
            handled = 1;
            low = code;
            result = func_800A3E00(low, arg0);
            switch (result) {
            case 2:
                return 1;
            case 1:
                return 0;
            default:
                break;
            }
            err = func_800A3808((s32)&code, arg0);
            if (err != 0) {
                return 0;
            }
            if (code == 442 || code == 441) {
                break;
            }
        }
        if (code == 441) {
            handled = 1;
            if (((Stream *)arg0)->unk_214 != 0) {
                return 1;
            }
            func_800A3E00(255, arg0);
            ((Stream *)arg0)->unk_214 = 1;
            return 1;
        }
        if (err != 0) {
            return 1;
        }
        if (handled == 0) {
            code = func_800A38F8(((Stream *)arg0)->unk_208);
            if (code == -1) {
                ((Stream *)arg0)->unk_204 = 1;
                return 0;
            }
        }
    }
}
