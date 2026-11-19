typedef unsigned char u8;
typedef signed int s32;

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[0x14];
} Entry;

extern Entry D_80057BB4[];

void func_800133C8(void) {
    s32 i;

    for (i = 0; i < 3; i++) {
        D_80057BB4[i].unk_00 = 0;
    }
}
