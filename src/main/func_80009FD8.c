typedef unsigned char u8;
typedef signed int s32;

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ u8 unk_08[0x3C];
} Entry;

extern Entry D_800B82A0[];
extern s32 D_800B61A4;
extern s32 D_800B82E0;
extern s32 D_800BA5E0[];
extern s32 D_800BEE50;

void func_80009FD8(void) {
    s32 i;

    for (i = 0; i < 70; i++) {
        D_800B82A0[i].unk_00 = 0;
        D_800B82A0[i].unk_04 = i;
    }
    D_800BEE50 = 0;
    D_800B82A0[0].unk_00 = 0;
    D_800B82E0 = 0;
    D_800B61A4 = 0;
    for (i = 0; i < 70; i++) {
        D_800BA5E0[i] = 0;
    }
}
