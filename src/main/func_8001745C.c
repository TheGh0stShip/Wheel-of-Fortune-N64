typedef unsigned char u8;
typedef signed int s32;

typedef struct {
    /* 0x00 */ u8 unk_00[0x4];
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ u8 unk_08[0x28];
    /* 0x30 */ s32 *unk_30;
} Obj;

void func_80016C78();
s32 func_8000B3B0(s32 arg0, s32 arg1, s32 arg2);
void func_80016944(s32 arg0, s32 arg1);

void func_8001745C(s32 arg0) {
    s32 handle;

    handle = func_8000B3B0(((Obj *)arg0)->unk_04, (s32)func_80016C78, 0x3000000);
    if (handle == 0) {
        return;
    }
    *((Obj *)arg0)->unk_30 = handle;
    func_80016944(handle, 1);
}
