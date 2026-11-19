typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;

struct n64dk_r12 { s32 w[3]; };

typedef struct {
    /* 0x00 */ u8 unk_00[0x10];
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ u8 unk_14[0x30];
    /* 0x44 */ s32 unk_44;
} Obj;

typedef struct {
    /* 0x00 */ Obj *unk_00;
    /* 0x04 */ s32 unk_04;
} State;

typedef struct {
    /* 0x00 */ u8 unk_00[0x30];
    /* 0x30 */ State *unk_30;
} Task;

typedef struct {
    /* 0x00 */ u16 unk_00;
    /* 0x02 */ u8 unk_02[0x2];
    /* 0x04 */ u16 unk_04;
    /* 0x06 */ u8 unk_06[0x22];
} Pos;

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ u8 unk_08[0x20];
} Entry;

extern Pos D_8005B712[];
extern Entry D_8005B730[];
extern s32 D_8005BA80[];
extern s32 D_800B619C;
extern s32 D_800B96A8;
extern s32 D_800B96B4;
extern s32 D_800B96C0;
extern s32 D_800FB808;
s32 func_80002CE0(s32 arg0);
void func_8000AAB0(s32 arg0, s32 arg1, s32 arg2);
s32 func_8000ACE8(s32 arg0);
void func_80016B9C(s32 arg0);
void func_80032AD4(s32 arg0);
void func_80032B80(void);

struct n64dk_r12 func_80029098(s32 arg1) {
    s32 event;
    s32 index;
    struct n64dk_r12 result;
    Obj *obj;

    result.w[1] = 1;
    result.w[0] = 0;
    obj = ((Task *)arg1)->unk_30->unk_00;
    for (;;) {
        event = func_8000ACE8(arg1);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 8:
            if (D_800B619C < D_800B96C0) {
                func_80032B80();
            }
            func_80032AD4(2);
            ((Task *)arg1)->unk_30->unk_04 = 0;
            break;
        case 6:
            if (D_800B619C == 6) {
                func_80032AD4(80);
            } else {
                func_80016B9C(17);
                D_800B96A8++;
            }
            result.w[1] = 0;
            result.w[0] = 1;
            return result;
        }
    }
    index = ((Task *)arg1)->unk_30->unk_04;
    if (D_8005B730[index].unk_04 == 0 || index >= 22) {
        if (D_800B619C != 6) {
            func_80002CE0(D_800FB808 + 139);
        }
        func_8000AAB0(arg1, 6, 0);
        result.w[1] = 1;
        result.w[0] = 20 / D_800B96B4;
        return result;
    }
    obj->unk_10 = D_8005B712[index].unk_00;
    obj->unk_12 = D_8005B712[index].unk_04 - 4;
    D_8005B730[index].unk_00 = D_8005B730[index].unk_04;
    if (index >= 16) {
        index = index % 16;
    }
    obj->unk_44 = D_8005BA80[index];
    ((Task *)arg1)->unk_30->unk_04++;
    return result;
}
