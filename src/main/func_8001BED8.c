#include "wof.h"

struct n64dk_r12 { s32 w[3]; };

typedef struct {
    /* 0x00 */ u8 unk_00[0x4];
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ u8 unk_08[0x4];
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ s8 unk_10;
} State;

typedef struct {
    /* 0x00 */ u8 unk_00[0x30];
    /* 0x30 */ State *unk_30;
} Task;

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[0x110];
} Player;

extern Player D_800B9A8C[];
extern f64 D_80001408;
extern s32 func_80010574;
extern s32 func_8001BC44;
extern u8 D_800B61B5;
extern s32 D_800B96B4;
extern s32 D_800FB808;
s32 func_80002CE0(s32 arg0);
s32 func_80007888(s32 arg0, s32 arg1);
void func_80007DAC(s32 arg0);
s32 func_800082E4(void);
f32 func_80008628(void);
s32 func_800088E4(void);
s32 func_80009C98(s32 arg0);
s32 func_8000A56C(s32 arg0, s32 arg1);
void func_8000A850(s32 arg0);
s32 func_8000A990(s32 arg0, s32 arg1);
void func_8000AAB0(s32 arg0, s32 arg1, s32 arg2);
s32 func_8000ACE8(s32 arg0);
void func_8000AD9C(s32 arg0);
s32 func_80017548(void);
void func_80017C00(s32 arg0, s32 arg1);
s32 func_8001A894(f32 arg0, s32 arg1);
s32 func_8001A97C(f32 arg0);
void func_80029974(s32 arg0);
void func_8002EB90(s32 arg0);
void func_8002FD50(void);

struct n64dk_r12 func_8001BED8(s32 arg1) {
    struct n64dk_r12 sp10;
    s32 task;
    s32 pad0;
    s32 event;
    f32 ratio;

    sp10.w[1] = 1;
    sp10.w[0] = 0;
    if (((Task *)arg1)->unk_30->unk_04 != D_800FB808) {
        func_8000AD9C(arg1);
        return sp10;
    }
    task = func_8000A990(0x5000000, -1);
    while ((event = func_8000ACE8(arg1)) != 0) {
        switch (event) {
        case 8:
            func_80017C00(3, 1);
            switch (func_800082E4()) {
            case 4:
                if (func_80009C98(100) >= 11) {
                    func_8002EB90(func_8001A894(((Task *)arg1)->unk_30->unk_0C, arg1) & 255);
                } else {
                    func_8002EB90(func_8001A97C(((Task *)arg1)->unk_30->unk_0C) & 255);
                }
                break;
            case 2:
                func_8002EB90(func_8001A97C(((Task *)arg1)->unk_30->unk_0C) & 255);
                break;
            case 3:
                func_8002EB90(func_8001A894(((Task *)arg1)->unk_30->unk_0C, arg1) & 255);
                break;
            }
            func_8000AAB0(arg1, 5, 0);
            sp10.w[1] = 1;
            sp10.w[0] = 60 / D_800B96B4;
            return sp10;
            break;
        case 5:
            func_80002CE0(D_800B9A8C[D_800FB808].unk_00 + (D_800B61B5 - 65));
            func_8000AAB0(arg1, 44, 0);
            sp10.w[1] = 1;
            sp10.w[0] = 30 / D_800B96B4;
            return sp10;
        case 44:
            task = func_8000A990(0x5010000, -1);
            func_8000AAB0(task, 23, 0);
            if (func_80007888(D_800B61B5, 2) > 0) {
                func_80007DAC(D_800B61B5);
                task = func_8000A56C((s32)&func_80010574, 0x1000000);
                ((Task *)task)->unk_30->unk_10 = D_800B61B5;
                sp10.w[1] = 2;
                sp10.w[0] = 6;
                return sp10;
            } else {
                func_80002CE0(1);
                func_80017548();
                func_8000A850(24);
                func_8000A850(31);
                func_8000AAB0(task, 31, 0);
                sp10.w[1] = 0;
                sp10.w[0] = 0;
                return sp10;
            }
        case 6:
            func_80029974(0);
            func_8002FD50();
            ratio = func_80008628();
            if (ratio > D_80001408) {
                task = func_8000A56C((s32)&func_8001BC44, ((Task *)arg1)->unk_30->unk_04 | 0x2000300);
                ((Task *)task)->unk_30->unk_04 = ((Task *)arg1)->unk_30->unk_04;
                ((Task *)task)->unk_30->unk_0C = ((Task *)arg1)->unk_30->unk_0C;
                sp10.w[1] = 2;
                sp10.w[0] = 10;
                return sp10;
            } else {
                sp10.w[1] = 1;
                sp10.w[0] = 0;
                return sp10;
            }
        case 33:
            func_80002CE0(1);
        case 10:
            if (func_800088E4() != 1) {
                func_80017548();
            }
            func_8000A850(24);
            func_8000A850(31);
            func_8000AAB0(task, 31, 0);
            sp10.w[1] = 0;
            sp10.w[0] = 0;
            return sp10;
        case 34:
            sp10.w[1] = 0;
            sp10.w[0] = 0;
            return sp10;
        }
    }
    return sp10;
}
