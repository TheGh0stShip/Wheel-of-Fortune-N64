typedef unsigned char u8;
typedef signed int s32;

typedef struct {
    /* 0x00 */ u8 unk_00[0x10];
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ u8 unk_18[0x4];
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ u8 unk_20[0x8];
} Entry;

void func_800226BC(s32 arg0, s32 arg1, s32 arg2) {
    s32 i;

    for (i = 0; i < arg1; i++) {
        ((Entry *)arg0)[i].unk_10 = arg2;
        ((Entry *)arg0)[i].unk_1C = ((Entry *)arg0)[i].unk_14;
    }
}
