#include "wof.h"

typedef struct {
    /* 0x00 */ u8 unk_00[0xC];
    /* 0x0C */ f32 unk_0C;
} State;

typedef struct {
    /* 0x00 */ u8 unk_00[0x30];
    /* 0x30 */ State *unk_30;
} Task;

typedef struct {
    /* 0x000 */ s32 unk_00;
    /* 0x004 */ u8 unk_04[0x110];
} Player;

extern Player D_800B9990[];
extern f64 D_800011CC;
extern f64 D_800011D4;
extern f32 D_800011DC;
extern f32 D_800011E0;
extern f64 D_800011E4;
extern s8 D_800B61B5;
extern s32 D_800B61C0;
extern s32 D_800B6AE0;
extern s32 D_800B96A0;
extern s32 D_800B9CF8;
extern s32 D_800B9CFC;
extern s32 D_800B9D00;
extern s32 D_800FB808;

void func_8001AA60(s32 arg0) {
    s32 task;
    s32 sp14;
    f32 score;
    f32 sp1C;
    f32 sp20;

    sp14 = 0;
    sp20 = func_80008628();
    task = func_8000A990(0x5000000, -1);
    if (D_800B9D00 != 0) {
        if (D_800B96A0 != 0) {
            if (sp20 > D_800011CC) {
                D_800B61B5 = 50;
                func_8000AAB0(arg0, 14, 0);
                func_8000AAB0(task, 27, 0);
                return;
            }
        }
        if (sp20 > D_800011D4 || D_800B9CF8 == 0) {
            D_800B61B5 = 50;
            func_8000AAB0(arg0, 14, 0);
            func_8000AAB0(task, 27, 0);
            return;
        }
    }
    if (D_800B9CF8 != 0) {
        sp1C = (f32)func_80009C98(100);
        sp1C = sp1C / D_800011DC;
        score = (f32)func_80009A74((s32)&D_800B61C0);
        score = score / D_800011E0;
        score = score * D_800011E4;
        score = score + sp1C;
        switch (func_800084E8()) {
        case 4:
            if (score < ((Task *)arg0)->unk_30->unk_0C || D_800B9990[D_800FB808].unk_00 < 250) {
                D_800B61B5 = 48;
                func_8000AAB0(arg0, 12, 0);
            } else {
                D_800B61B5 = 49;
                func_8000AAB0(arg0, 13, 0);
            }
            break;
        case 3:
            D_800B61B5 = 48;
            func_8000AAB0(arg0, 12, 0);
            break;
        case 2:
            D_800B61B5 = 49;
            func_8000AAB0(arg0, 13, 0);
            break;
        }
    } else if (D_800B9CFC != 0) {
        if (func_80009A74((s32)&D_800B6AE0) != 0) {
            D_800B61B5 = 49;
            func_8000AAB0(arg0, 13, 0);
        } else {
            D_800B61B5 = 48;
            func_8000AAB0(arg0, 12, 0);
        }
    }
    func_8000AAB0(task, 27, 0);
}
