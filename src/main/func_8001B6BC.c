typedef signed char s8;
typedef unsigned char u8;
typedef signed int s32;
typedef float f32;
struct n64dk_r12 { s32 w[3]; };

typedef struct {
    /* 0x00 */ u8 unk_00[0x4];
    /* 0x04 */ s32 player;
    /* 0x08 */ u8 unk_08[0x4];
    /* 0x0C */ f32 unk_0C;
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
s32 func_80002CE0(s32 arg0);
s32 func_800051B4(); /* called without a prototype */
s32 func_80007888(s32 arg0, s32 arg1);
void func_80007DAC(s32 arg0);
s32 func_8000A56C(s32 arg0, s32 arg1);
void func_8000A850(s32 arg0);
s32 func_8000A990(s32 arg0, s32 arg1);
void func_8000AAB0(s32 arg0, s32 arg1, s32 arg2);
s32 func_8000ACE8(s32 arg0);
void func_8000AD9C(s32 arg0);
struct n64dk_r12 func_80010574(s32 arg1);
s32 func_80017548(void);
void func_80017C00(s32 arg0, s32 arg1);
s32 func_8001A97C(f32 arg0);
void func_8002EB90(s32 arg0);

struct n64dk_r12 func_8001B6BC(s32 arg1) {
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
                ret.w[1] = 1;
                ret.w[0] = 30 / D_800B96B4;
                return ret;
            } else {
                func_80017C00(3, 1);
                func_8002EB90(func_8001A97C(((Object *)arg1)->data->unk_0C) & 255);
                func_8000AAB0(arg1, 5, 0);
                ret.w[1] = 1;
                ret.w[0] = 60 / D_800B96B4;
                return ret;
            }
            break;
        case 5:
            func_80002CE0(D_800B9990[D_800FB808].unk_FC + (D_800B61B5 - 'A'));
            func_8000AAB0(arg1, 44, 0);
            ret.w[1] = 1;
            ret.w[0] = 30 / D_800B96B4;
            return ret;
        case 44:
            task = func_8000A990(0x5010000, -1);
            func_8000AAB0(task, 23, 0);
            if (func_80007888(D_800B61B5, 1) > 0) {
                func_80007DAC(D_800B61B5);
                task = func_8000A56C((s32)func_80010574, 0x1000000);
                ((Object *)task)->data->unk_10 = D_800B61B5;
                ret.w[1] = 2;
                ret.w[0] = 6;
            } else {
                func_80002CE0(1);
                if (func_80017548() != 0) {
                    func_8000A850(9);
                    func_8000A850(24);
                }
                ret.w[1] = 0;
                ret.w[0] = 0;
                return ret;
            }
            break;
        case 51:
            func_8000A850(9);
            func_80002CE0(150);
            func_800051B4(D_800B9990[D_800FB808].unk_14, 30, 0.8);
            func_80017548();
            ret.w[1] = 0;
            ret.w[0] = 0;
            return ret;
        case 6:
            func_8000A850(24);
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
