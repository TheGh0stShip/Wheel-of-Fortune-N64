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
} State;

typedef struct {
    /* 0x00 */ u8 unk_00[0x30];
    /* 0x30 */ State *state;
} Task;

typedef struct {
    /* 0x000 */ s32 unk_00;
    /* 0x004 */ u8 unk_04[0xF4];
    /* 0x0F8 */ s32 unk_F8;
    /* 0x0FC */ s32 unk_FC;
    /* 0x100 */ s32 unk_100;
    /* 0x104 */ s32 unk_104;
    /* 0x108 */ u8 unk_108[0xC];
} Player;

extern Player D_800B9998[];
extern s32 func_80017DBC;
extern s32 func_8001AE18;
extern s32 func_8001B6BC;
extern s32 func_8001BC44;
extern s32 func_8001BED8;
extern s32 D_800B619C;
extern s8 D_800B61B5;
extern s32 D_800B96A0;
extern s32 D_800B96A8;
extern s32 D_800B96B4;
extern s32 D_800B96C0;
extern s32 D_800B9CF0;
extern s32 D_800BCA00;
extern s32 D_800BEE54;
extern s32 D_800FB808;
s32 func_80002CE0(s32 arg0);
s32 func_80007EEC(s32 arg0);
s32 func_800082E4(void);
s32 func_8000A56C(s32 arg0, s32 arg1);
void func_8000A850(s32 arg0);
s32 func_8000A990(s32 arg0, s32 arg1);
void func_8000AAB0(s32 arg0, s32 arg1, s32 arg2);
s32 func_8000ACE8(s32 arg0);
void func_80015D4C(void);
void func_80016008(void);
void func_800177A4(void);
void func_80017C00(s32 arg0, s32 arg1);
void func_8001AA60(s32 arg0);
s32 func_8003CE58(void);

struct n64dk_r12 func_8001C584(s32 arg1) {
    s32 event;
    struct n64dk_r12 ret;
    s32 task;

    ret.w[1] = 1;
    ret.w[0] = 0;
    if (((Task *)arg1)->state->player != D_800FB808) {
        while ((event = func_8000ACE8(arg1)) != 0) {
            switch (event) {
            case 34:
                ret.w[1] = 0;
                ret.w[0] = 0;
                return ret;
            case 42:
                ret.w[1] = 0;
                ret.w[0] = 0;
                return ret;
            }
        }
        return ret;
    }
    while ((event = func_8000ACE8(arg1)) != 0) {
        switch (event) {
        case 38:
            func_80002CE0(D_800B9998[D_800FB808].unk_104);
            D_800B9998[D_800FB808].unk_00 = 0;
            /* fallthrough */
        case 3:
        case 9:
        case 10:
        case 31:
            func_80017C00(3, 1);
            task = func_8000A990(0x5000000, -1);
            func_8000AAB0(task, 24, 0);
            if (func_80007EEC(1) == 1) {
                func_8000AAB0(task, 21, 0);
                func_80016008();
                D_800B96A8 += 3;
                func_80002CE0(5);
                task = func_8000A56C((s32)&func_80017DBC, ((Task *)arg1)->state->player | 0x2000500);
                ((Task *)task)->state->player = ((Task *)arg1)->state->player;
                if (D_800B9CF0 != 0 || D_800B619C == D_800B96C0 - 1) {
                    ret.w[1] = 0;
                    ret.w[0] = 0;
                } else {
                    ret.w[1] = 2;
                    ret.w[0] = 39;
                }
                return ret;
            }
            if (D_800BEE54 == 0 && func_800082E4() == 2) {
                D_800BEE54 = 1;
                func_80002CE0(6);
            }
            func_8000AAB0(arg1, 28, 0);
            ret.w[1] = 1;
            ret.w[0] = 20 / D_800B96B4;
            return ret;
        case 8:
            ret.w[1] = 2;
            ret.w[0] = 40;
            return ret;
        case 40:
            func_80015D4C();
            func_8000AAB0(arg1, 1, 0);
            func_80017C00(3, 1);
            ret.w[1] = 1;
            ret.w[0] = 60 / D_800B96B4;
            return ret;
        case 1:
        case 32:
            func_8000A850(24);
            if (D_800BCA00 == 1) {
                task = func_8000A56C((s32)&func_8001BED8, ((Task *)arg1)->state->player | 0x2030400);
                ((Task *)task)->state->player = ((Task *)arg1)->state->player;
                ((Task *)task)->state->unk_0C = ((Task *)arg1)->state->unk_0C;
                ret.w[1] = 2;
                ret.w[0] = 31;
                return ret;
            }
            func_8000AAB0(arg1, 28, 0);
            ret.w[1] = 1;
            ret.w[0] = 30 / D_800B96B4;
            func_80017C00(3, 1);
            D_800B96A8++;
            return ret;
        case 15:
            func_8000A850(24);
            if (D_800BCA00 == 1) {
                task = func_8000A56C((s32)&func_8001BED8, ((Task *)arg1)->state->player | 0x2030400);
                ((Task *)task)->state->player = ((Task *)arg1)->state->player;
                ((Task *)task)->state->unk_0C = ((Task *)arg1)->state->unk_0C;
                ret.w[1] = 2;
                ret.w[0] = 31;
                return ret;
            }
            func_8000AAB0(arg1, 12, 0);
            ret.w[1] = 1;
            ret.w[0] = 60 / D_800B96B4;
            func_80017C00(3, 1);
            return ret;
        case 28:
            if (D_800BCA00 == 1) {
                task = func_8000A56C((s32)&func_8001BED8, ((Task *)arg1)->state->player | 0x2030400);
                ((Task *)task)->state->player = ((Task *)arg1)->state->player;
                ((Task *)task)->state->unk_0C = ((Task *)arg1)->state->unk_0C;
                ret.w[1] = 2;
                ret.w[0] = 31;
                return ret;
            }
            func_8001AA60(arg1);
            ret.w[1] = 1;
            ret.w[0] = 60 / D_800B96B4;
            return ret;
        case 12:
            if (func_8003CE58() % 100 < 33) {
                func_80002CE0(D_800B9998[D_800FB808].unk_F8);
            }
            D_800B96A0 = 0;
            task = func_8000A990(0x5000000, -1);
            func_8000AAB0(task, 23, 0);
            task = func_8000A56C((s32)&func_8001AE18, ((Task *)arg1)->state->player | 0x2000100);
            ((Task *)task)->state->player = ((Task *)arg1)->state->player;
            ((Task *)task)->state->unk_0C = ((Task *)arg1)->state->unk_0C;
            ret.w[1] = 2;
            ret.w[0] = 3;
            return ret;
        case 13:
            func_80002CE0(D_800B9998[D_800FB808].unk_FC);
            D_800B96A0 = 0;
            task = func_8000A990(0x5000000, -1);
            func_8000AAB0(task, 23, 0);
            task = func_8000A56C((s32)&func_8001B6BC, ((Task *)arg1)->state->player | 0x2000200);
            ((Task *)task)->state->player = ((Task *)arg1)->state->player;
            ((Task *)task)->state->unk_0C = ((Task *)arg1)->state->unk_0C;
            ret.w[1] = 2;
            ret.w[0] = 9;
            return ret;
        case 14:
            func_80002CE0(D_800B9998[D_800FB808].unk_100);
            task = func_8000A990(0x5000000, -1);
            func_8000AAB0(task, 23, 0);
            task = func_8000A56C((s32)&func_8001BC44, ((Task *)arg1)->state->player | 0x2000300);
            ((Task *)task)->state->player = ((Task *)arg1)->state->player;
            ((Task *)task)->state->unk_0C = ((Task *)arg1)->state->unk_0C;
            ret.w[1] = 2;
            ret.w[0] = 10;
            return ret;
        case 37:
            D_800B96A0 = 0;
            task = func_8000A990(0x5000000, -1);
            D_800B61B5 = '3';
            func_8000AAB0(task, 27, 1);
            func_8000AAB0(arg1, 38, 0);
            ret.w[1] = 1;
            ret.w[0] = 60 / D_800B96B4;
            return ret;
        case 39:
            func_800177A4();
            if (((Task *)arg1)->state->player != D_800FB808) {
                ret.w[1] = 2;
                ret.w[0] = -1;
            } else {
                ret.w[1] = 1;
                ret.w[0] = 0;
            }
            return ret;
        case 30:
            ret.w[1] = 2;
            ret.w[0] = 32;
            return ret;
        case 34:
            ret.w[1] = 0;
            ret.w[0] = 0;
            return ret;
        }
    }
    return ret;
}
