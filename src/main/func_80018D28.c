#include "wof.h"
#include "func_800051B4.h"

typedef struct {
    /* 0x00 */ u8 unk_00[0x4];
    /* 0x04 */ s32 player;
    /* 0x08 */ u8 unk_08[0x8];
    /* 0x10 */ s8 unk_10;
} Data;

typedef struct {
    /* 0x00 */ u8 unk_00[0x30];
    /* 0x30 */ Data *data;
} Object;

typedef struct {
    /* 0x000 */ s32 unk_00;
    /* 0x004 */ u8 unk_04[0x10];
    /* 0x014 */ s32 unk_14;
    /* 0x018 */ u8 unk_18[0xE4];
    /* 0x0FC */ s32 unk_FC;
    /* 0x100 */ u8 unk_100[0x14];
} Player;

extern Player D_800B9990[];
extern u8 D_800B61B5;
extern s32 D_800B96B4;
extern s32 D_800FB808;

struct n64dk_r12 func_80018D28(s32 arg1) {
    struct n64dk_r12 ret;
    s32 task;
    s32 pad0;
    s32 event;

    ret.w[1] = 1;
    ret.w[0] = 0;
    if (((Object *)arg1)->data->player != D_800FB808) {
        func_8000AD9C(arg1);
        return ret;
    }
    for (;;) {
        event = func_8000ACE8(arg1);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 8:
            if (D_800B9990[D_800FB808].unk_00 < 250) {
                func_8000AAB0(arg1, 51, 0);
                func_80002CE0(1);
                func_800051B4(D_800B9990[D_800FB808].unk_14, 30, 0.8f);
                ret.w[1] = 1;
                ret.w[0] = 30 / D_800B96B4;
                return ret;
            } else {
                if (func_800084E8() == 3) {
                    func_80021B04(1, 16);
                    ret.w[1] = 2;
                    ret.w[0] = 16;
                    return ret;
                } else {
                    func_80017C00(3, 0);
                    func_8002EB40();
                    ret.w[1] = 2;
                    ret.w[0] = 5;
                }
            }
            break;
        case 16:
            func_8000A850(9);
            ret.w[1] = 0;
            ret.w[1] = 0;
            return ret;
        case 5:
            func_80002CE0(D_800B9990[D_800FB808].unk_FC + (D_800B61B5 - 'A'));
            func_8000AAB0(arg1, 44, 0);
            ret.w[1] = 1;
            ret.w[0] = 30 / D_800B96B4;
            return ret;
        case 44:
            if (func_80007888(D_800B61B5, 1) > 0) {
                func_80007DAC(D_800B61B5);
                task = func_8000A56C((s32)func_80010574, 0x1000000);
                ((Object *)task)->data->unk_10 = D_800B61B5;
                ret.w[1] = 2;
                ret.w[0] = 6;
            } else {
                func_80002CE0(1);
                func_800051B4(D_800B9990[D_800FB808].unk_14, 30, 0.8f);
                if (func_80017548() != 0) {
                    func_8000A850(9);
                }
                ret.w[1] = 0;
                ret.w[0] = 0;
                return ret;
            }
            break;
        case 51:
            func_8000AAB0(arg1, 52, 0);
            func_80002CE0(150);
            ret.w[1] = 1;
            ret.w[0] = 60 / D_800B96B4;
            return ret;
        case 52:
            func_8000A850(9);
            func_80017548();
            ret.w[1] = 0;
            ret.w[0] = 0;
            return ret;
        case 6:
            func_8000A850(9);
            ret.w[1] = 0;
            ret.w[0] = 0;
            return ret;
        case 34:
            ret.w[1] = 0;
            ret.w[0] = 0;
            return ret;
        }
    }
    return ret;
}
