typedef signed char s8;
typedef unsigned char u8;
typedef unsigned short u16;
typedef signed int s32;
struct n64dk_r12 { s32 w[3]; };

typedef struct {
    /* 0x00 */ u8 unk_00[0x4];
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
} State;

typedef struct {
    /* 0x00 */ u8 unk_00[0x30];
    /* 0x30 */ State *unk_30;
} Task;

typedef struct {
    u8 unk_00[0x20];
} Item;

extern s32 D_80001608;
extern Item D_80058AA8[];
extern s32 D_80058AC8;
extern s32 D_80058AE8;
extern s32 D_80058B08;
extern s32 D_80058B28;
extern u16 D_800B96B0;
extern s32 D_800B96B4;
extern s8 D_800B9956;
extern s8 D_800B9957;
s32 func_80002CE0(s32 arg0);
void func_8000315C(void);
void func_80009F38(s32 *arg0);
void func_8000AAB0(s32 arg0, s32 arg1, s32 arg2);
s32 func_8000ACE8(s32 arg0);
void func_8000ADEC(s32 arg0);
void func_8000AE70(s32 arg0, s32 arg1, s32 arg2);
void func_8000AF00(void);
void func_8000B9FC(s32 arg0);
void func_8000BE6C(void);
void func_80022784(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_800229D0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_80022BC8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_80022DC0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_80022FE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_8002500C(void);
void func_80025FA8(void);
void func_80026DEC(void);
void func_80026E50(void);

struct n64dk_r12 func_80025150(s32 arg1) {
    s32 event;
    struct n64dk_r12 ret;
    s8 pad0;

    ret.w[1] = 1;
    ret.w[0] = 0;
    for (;;) {
        event = func_8000ACE8(arg1);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 8:
            ((Task *)arg1)->unk_30->unk_08 = 0;
            ((Task *)arg1)->unk_30->unk_04 = 0;
            func_80022784(arg1, (s32)&D_80058B28, (s32)&D_80058AA8, 1);
            func_80022784(arg1, (s32)&D_80058B28, (s32)&D_80058AC8, 0);
            func_80022784(arg1, (s32)&D_80058B28, (s32)&D_80058AE8, 0);
            func_80022784(arg1, (s32)&D_80058B28, (s32)&D_80058B08, 0);
            return ret;
        case 36:
            func_8000ADEC(arg1);
            func_8000AF00();
            func_8000B9FC(1);
            func_8000BE6C();
            ret.w[1] = 0;
            ret.w[0] = 0;
            return ret;
        }
    }
    if ((D_800B96B0 & 0xA000 & 0xFFFF) != 0) {
        func_80002CE0(42);
        ((Task *)arg1)->unk_30->unk_0C = 0;
        switch (((Task *)arg1)->unk_30->unk_08) {
        case 0:
            func_8002500C();
            func_8000B9FC(1);
            func_8000315C();
            func_8000AAB0(arg1, 36, 0);
            ret.w[1] = 1;
            ret.w[0] = 2;
            return ret;
            break;
        case 1:
            func_8000AE70(0xA000300, -256, 1);
            func_80025FA8();
            ret.w[1] = 0;
            ret.w[0] = 1;
            break;
        case 2:
            func_8000AE70(0xA000300, -256, 1);
            func_80026DEC();
            ret.w[1] = 0;
            ret.w[0] = 1;
            break;
        case 3:
            func_8000AE70(0xA000300, -256, 1);
            func_80026E50();
            ret.w[1] = 0;
            ret.w[0] = 1;
            break;
        default:
            func_80009F38(&D_80001608);
        }
    }
    if ((D_800B96B0 & 0x1000 & 0xFFFF) != 0) {
        func_80002CE0(42);
        func_8002500C();
        func_8000315C();
        func_8000B9FC(1);
        func_8000AAB0(arg1, 36, 0);
        ret.w[1] = 1;
        ret.w[0] = 2;
        return ret;
    } else if ((D_800B96B0 & 0x800 & 0xFFFF) != 0) {
        func_800229D0(arg1, (s32)&D_80058B28, (s32)&D_80058AA8, 4);
    } else if ((D_800B96B0 & 0x400 & 0xFFFF) != 0) {
        func_80022BC8(arg1, (s32)&D_80058B28, (s32)&D_80058AA8, 4);
    } else if ((D_800B96B0 & 0x200 & 0xFFFF) != 0) {
        func_80022DC0(arg1, (s32)&D_80058B28, (s32)&D_80058AA8[((Task *)arg1)->unk_30->unk_08], 0);
    } else if ((D_800B96B0 & 0x100 & 0xFFFF) != 0) {
        func_80022FE0(arg1, (s32)&D_80058B28, (s32)&D_80058AA8[((Task *)arg1)->unk_30->unk_08], 0);
    } else if ((D_800B96B0 & 0x4 & 0xFFFF) != 0) {
        return ret;
    } else if ((D_800B96B0 & 0x8 & 0xFFFF) != 0) {
        return ret;
    } else if ((D_800B96B0 & 0x4000 & 0xFFFF) != 0) {
        return ret;
    }
    if (((Task *)arg1)->unk_30->unk_0C <= 0) {
        if (D_800B9956 >= 41) {
            func_80022FE0(arg1, (s32)&D_80058B28, (s32)&D_80058AA8[((Task *)arg1)->unk_30->unk_08], 0);
        } else if (D_800B9956 < -40) {
            func_80022DC0(arg1, (s32)&D_80058B28, (s32)&D_80058AA8[((Task *)arg1)->unk_30->unk_08], 0);
        }
        if (D_800B9957 >= 41) {
            func_800229D0(arg1, (s32)&D_80058B28, (s32)&D_80058AA8, 4);
        } else if (D_800B9957 < -40) {
            func_80022BC8(arg1, (s32)&D_80058B28, (s32)&D_80058AA8, 4);
        }
    } else {
        ((Task *)arg1)->unk_30->unk_0C = ((Task *)arg1)->unk_30->unk_0C - D_800B96B4;
    }
    return ret;
}
