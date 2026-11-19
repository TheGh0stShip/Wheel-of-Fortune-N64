typedef unsigned char u8;
typedef signed int s32;
typedef float f32;

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[0x1C];
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ s32 unk_24;
} Data;

typedef struct {
    /* 0x00 */ u8 unk_00[0x30];
    /* 0x30 */ Data *data;
} Obj;

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[0x4];
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ u8 unk_0C[0x4];
} Board;

extern Board D_8005822C[];
void func_80021548(s32);
extern s32 D_80058488;
extern s32 D_80086D58;
extern s32 D_800B40C4;
extern s32 D_800B96A4;
extern s32 D_800BCA0C;
extern s32 D_800BCA28;
s32 func_8000A56C(s32 arg0, s32 arg1);
s32 func_8000B978(void);
void func_8000B9FC(s32 arg0);
s32 func_800211E4(s32, s32 *, f32, f32, s32);
s32 func_80021908(s32 arg0);
void func_8009CEC0(s32 arg0, s32 arg1);
void func_800A4E58(s32 arg0);

void func_800219B8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    Obj *obj;
    s32 sp1C;

    if (D_80086D58 != 0) {
        func_8000B9FC(1);
        func_800A4E58(0);
    }
    D_800BCA28 = arg0;
    D_800B96A4 = 0;
    obj = (Obj *)func_8000A56C((s32)func_80021548, 0x5010000);
    obj->data->unk_00 = func_800211E4((s32)obj, &D_80058488, arg2, arg3, arg0);
    obj->data->unk_24 = D_8005822C[arg0].unk_00;
    obj->data->unk_20 = arg1;
    D_800BCA0C = func_8000B978();
    D_800B40C4 = 0;
    sp1C = func_80021908(arg0);
    func_8009CEC0(sp1C, D_8005822C[arg0].unk_08);
}
