typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef float f32;

struct n64dk_r12 { s32 w[3]; };

typedef struct {
    /* 0x00 */ u8 unk_00[0x10];
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ u8 unk_16[0x12];
    /* 0x28 */ s32 unk_28;
    /* 0x2C */ s32 unk_2C;
    /* 0x30 */ s32 unk_30;
} Obj;

typedef struct {
    /* 0x00 */ Obj *unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ u8 unk_08[0x4];
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ f32 unk_14;
} State;

typedef struct {
    /* 0x00 */ u8 unk_00[0x30];
    /* 0x30 */ State *unk_30;
} Task;

extern s32 D_800B3994;
extern f32 D_800B61AC;
extern u16 D_800B96B0;
extern s32 D_800B96B4;
extern s32 D_800BEE24;
s32 func_80002C34(s32 arg0);
void func_8000315C(void);
void func_8000AAB0(s32 arg0, s32 arg1, s32 arg2);
s32 func_8000ACE8(s32 arg0);
void func_8000ADEC(s32 arg0);
void func_8000AF00(void);
void func_8000B9FC(s32 arg0);
void func_8000EE78(void);
void func_80026EB4(void);
s32 func_8003BEA8(f32 (*)[4], s32, s32, s32);
s32 func_8003C2A8(f32 (*)[4], s32, f32, s32);
s32 func_80041018(f32 (*)[4], f32 (*)[4], f32 (*)[4]);

struct n64dk_r12 func_8000BEA8(s32 arg1) {
    f32 mtx[4][4];
    f32 rot[4][4];
    struct n64dk_r12 result;
    Obj *obj;
    s32 event;

    obj = ((Task *)arg1)->unk_30->unk_00;
    result.w[1] = 1;
    result.w[0] = 0;
    for (;;) {
        event = func_8000ACE8(arg1);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 8:
            result.w[1] = 1;
            result.w[0] = 2;
            return result;
        case 36:
            func_8000ADEC(arg1);
            func_8000AF00();
            func_8000B9FC(1);
            func_80026EB4();
            result.w[1] = 0;
            result.w[0] = 1;
            return result;
        case 34:
            func_8000ADEC(arg1);
            func_8000AF00();
            func_8000B9FC(1);
            func_8000EE78();
            result.w[1] = 0;
            result.w[0] = 1;
            return result;
        }
    }
    if ((D_800B96B0 & 0x1000) != 0) {
        func_8000315C();
        func_8000AAB0(arg1, 36, 0);
        result.w[1] = 1;
        result.w[0] = 2;
        return result;
    }
    if (func_80002C34(((Task *)arg1)->unk_30->unk_04) != 0 || D_800B3994 >= 720) {
        func_8000ADEC(arg1);
        func_8000AF00();
        func_8000B9FC(1);
        func_8000EE78();
        result.w[1] = 0;
        result.w[0] = 1;
        return result;
    }
    result.w[1] = 1;
    result.w[0] = 0;
    if (D_800B3994 >= 269 && D_800B3994 < 318) {
        D_800BEE24 = D_800BEE24 + D_800B96B4 * 5;
    }
    D_800B61AC = D_800B61AC - D_800B96B4;
    D_800B3994 = D_800B3994 + D_800B96B4;
    func_8003C2A8(mtx, 0, D_800BEE24, 0);
    func_8003BEA8(rot, obj->unk_28, obj->unk_2C, obj->unk_30);
    func_80041018(mtx, rot, mtx);
    obj->unk_10 = ((Task *)arg1)->unk_30->unk_0C + mtx[3][0];
    obj->unk_12 = ((Task *)arg1)->unk_30->unk_10 + mtx[3][1];
    obj->unk_14 = ((Task *)arg1)->unk_30->unk_14 + mtx[3][2];
    if (D_800B3994 >= 721) {
        D_800B3994 = 720;
    }
    return result;
}
