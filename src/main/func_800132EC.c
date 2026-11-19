typedef unsigned char u8;
typedef signed int s32;

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ u8 unk_0C[0xC];
} Entry;

extern Entry D_80057BB4[];

void func_800132EC(s32 arg0) {
    s32 i;

    for (i = 0; i < 3; i++) {
        D_80057BB4[i].unk_00 = 0;
    }
    D_80057BB4[arg0].unk_00 = 1;
    D_80057BB4[arg0].unk_08 = D_80057BB4[arg0].unk_04;
}
