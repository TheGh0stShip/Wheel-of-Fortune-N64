#include "wof.h"
#include "func_800051B4.h"

typedef struct {
    /* 0x00 */ u8 unk_00[0x4];
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ u8 unk_08[0x8];
    /* 0x10 */ s8 unk_10;
} State;

typedef struct {
    /* 0x000 */ s32 unk_00;
    /* 0x004 */ u8 unk_04[0xE4];
    /* 0x0E8 */ s32 unk_E8;
    /* 0x0EC */ u8 unk_EC[0x28];
} Player;

extern Player D_800B99A4[];

struct n64dk_r12 func_80019630(s32 arg1) {
    struct n64dk_r12 ret;
    s32 task;
    s32 pad0;
    s32 event;

    ret.w[1] = 1;
    ret.w[0] = 0;
    if (((State *)((proc_t *)arg1)->unk_30)->unk_04 != D_800FB808) {
        func_8000AD9C(arg1);
        return ret;
    }
    task = func_8000A990(0x5000000, -1);
    while ((event = func_8000ACE8(arg1)) != 0) {
        switch (event) {
        case 8:
            func_80017C00(3, 0);
            func_8002EB40();
            ret.w[1] = 2;
            ret.w[0] = 5;
            break;
        case 5:
            func_80002CE0(D_800B99A4[D_800FB808].unk_E8 + (D_800B61B5 - 'A'));
            func_8000AAB0(arg1, 44, 0);
            ret.w[1] = 1;
            ret.w[0] = 30 / D_800B96B4;
            return ret;
        case 44:
            if (func_80007888(D_800B61B5, 2) > 0) {
                func_80007DAC(D_800B61B5);
                task = func_8000A56C((s32)&func_80010574, 0x1000000);
                ((State *)((proc_t *)task)->unk_30)->unk_10 = D_800B61B5;
                ret.w[1] = 2;
                ret.w[0] = 6;
            } else {
                func_80002CE0(1);
                func_800051B4(D_800B99A4[D_800FB808].unk_00, 30, 0.8f);
                func_80017548();
                func_8000A850(31);
                func_8000AAB0(task, 31, 0);
                ret.w[1] = 0;
                ret.w[0] = 0;
                return ret;
            }
            break;
        case 6:
            func_80029974(0);
            func_8002FD50();
            task = func_8000A56C((s32)&func_8001933C, ((State *)((proc_t *)arg1)->unk_30)->unk_04 | 0x2000300);
            ((State *)((proc_t *)task)->unk_30)->unk_04 = ((State *)((proc_t *)arg1)->unk_30)->unk_04;
            ret.w[1] = 2;
            ret.w[0] = 10;
            return ret;
        case 10:
            if (func_800088E4() != 1) {
                func_80017548();
            }
            func_8000A850(31);
            func_8000AAB0(task, 31, 0);
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
