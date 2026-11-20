#include "wof.h"

struct n64dk_r12 { s32 w[3]; };

typedef struct {
    /* 0x00 */ u8 unk_00[0x2C];
    /* 0x2C */ f32 unk_2C;
} Actor;

typedef struct {
    /* 0x00 */ Actor *actor;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ s32 unk_08;
} State;

typedef struct {
    /* 0x00 */ u8 unk_00[0x8];
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ u8 unk_0C[0x24];
    /* 0x30 */ State *state;
} Obj;

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[0x110];
} Player;

extern Player D_800B99A4[];
extern f32 D_80000BB4;
extern f32 D_80000BB8;
extern f64 D_80000BBC;
extern f32 D_80000BC4;
extern f32 D_80000BC8;
extern f64 D_80000BCC;
extern f32 D_80000BD4;
extern f32 D_80000BD8;
extern s32 D_800581F0[];
extern s32 D_800B96B4;
extern u16 D_800BC6F8;
extern f32 D_800BCCF0;
extern s32 D_800FB808;
s32 func_80002CE0(s32 arg0);
s32 func_800051B4(); /* called without a prototype */
void func_80009108(f32 arg0);
s32 func_80009C98(s32 arg0);
s32 func_8000ACE8(s32 arg0);
s32 func_8000B5DC(s32 arg0, s32 arg1);

struct n64dk_r12 func_8000F274(s32 arg1) {
    struct n64dk_r12 result;
    Actor *actor;
    Actor *target;
    f32 sp28;
    f32 sp2C;
    s32 sp30;
    s32 event;

    for (;;) {
        event = func_8000ACE8(arg1);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 34:
            result.w[1] = 0;
            result.w[0] = 1;
            return result;
        }
    }
    actor = ((Obj *)arg1)->state->actor;
    result.w[1] = 1;
    result.w[0] = 0;
    target = (Actor *)func_8000B5DC(0x4010000, 0xFFFF0000);
    if (target == 0) {
        return result;
    }
    sp28 = target->unk_2C + (f32)D_800581F0[((Obj *)arg1)->unk_08 & 255];
    sp30 = (s32)(sp28 / D_80000BB4);
    sp28 = sp28 - (f32)(sp30 * 5);
    if ((f64)((D_800BCCF0 / D_80000BB8) * (f32)D_800B96B4) > D_80000BBC) {
        sp2C = sp28 * D_80000BC4 + D_80000BC8;
        if ((((Obj *)arg1)->unk_08 & 255) == D_800FB808) {
            if (D_800B99A4[D_800FB808].unk_00 < 4) {
                func_800051B4(D_800B99A4[D_800FB808].unk_00, 2, 1.0);
            }
            if ((u32)D_800BC6F8 < 16) {
                func_80002CE0(func_80009C98(11) + 27);
            }
        }
    } else {
        if ((f64)sp28 > D_80000BCC && sp28 < D_80000BD4) {
            sp2C = sp28 * D_80000BD8;
        } else {
            sp28 = 0;
            sp2C = 0;
        }
        if ((((Obj *)arg1)->unk_08 & 255) == D_800FB808) {
            if (sp2C - actor->unk_2C < 0.0f) {
                if (((Obj *)arg1)->state->unk_08 > 0) {
                    func_80002CE0(func_80009C98(2) + 25);
                    if (D_800B99A4[D_800FB808].unk_00 < 4) {
                        func_800051B4(D_800B99A4[D_800FB808].unk_00, 5, 1.0);
                    }
                }
            }
        }
    }
    if ((((Obj *)arg1)->unk_08 & 255) == D_800FB808) {
        func_80009108(target->unk_2C + (f32)D_800581F0[D_800FB808] - sp28 + ((Obj *)arg1)->state->unk_04);
    }
    ((Obj *)arg1)->state->unk_08 = (s32)(sp2C - actor->unk_2C);
    actor->unk_2C = sp2C;
    return result;
}
