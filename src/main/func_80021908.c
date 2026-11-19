typedef unsigned char u8;
typedef signed int s32;

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[0x4];
    /* 0x08 */ s32 *unk_08;
    /* 0x0C */ u8 unk_0C[0x4];
} Entry;

extern Entry D_80058228[];
void func_80006828(s32 arg0, s32 arg1, s32 arg2);
s32 func_8000B924(s32 arg0);

s32 func_80021908(s32 arg0) {
    s32 buf;

    buf = func_8000B924(*D_80058228[arg0].unk_08 + 1);
    func_80006828(D_80058228[arg0].unk_00, buf, *D_80058228[arg0].unk_08 + 1);
    return buf;
}
