#include "wof.h"

struct n64dk_r12 { s32 w[3]; };

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[0x110];
} Player;

extern Player D_800B9994[];
extern s32 func_8002842C;
extern s32 func_8002B730;
extern s32 D_800B96A8;
extern s32 D_800B96B4;
extern s32 D_800FB808;
s32 func_80002CE0(s32 arg0);
s32 func_8000A56C(s32 arg0, s32 arg1);
s32 func_8000ACE8(s32 arg0);
void func_8000AE70(s32 arg0, s32 arg1, s32 arg2);
void func_80016008(void);
void func_80016B9C(s32 arg0);
s32 func_80027218(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_80032AD4(s32 arg0);
void func_80034950(void);

struct n64dk_r12 func_8002BE84(s32 arg1) {
    s32 event;
    struct n64dk_r12 sp18;
    s8 pad0;

    sp18.w[1] = 1;
    sp18.w[0] = 0;
    while ((event = func_8000ACE8(arg1)) != 0) {
        switch (event) {
        case 8:
            D_800B96A8 = D_800B96A8 + 6;
            func_80032AD4(1);
            func_80016008();
            func_80034950();
            func_8000AE70(0x5050200, -1, 1);
            D_800B9994[D_800FB808].unk_00 = D_800B9994[D_800FB808].unk_00 + 0x61A8;
            func_80002CE0(5);
            func_80027218(arg1, 0, (s32)&func_8002842C, 0x5050000);
            sp18.w[0] = 320 / D_800B96B4;
            return sp18;
        }
    }
    func_80016B9C(20);
    func_8000A56C((s32)&func_8002B730, 0x6000000);
    sp18.w[1] = 0;
    sp18.w[0] = 1;
    return sp18;
}
