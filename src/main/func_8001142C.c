typedef signed char s8;
typedef unsigned char u8;
typedef signed int s32;

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[0x18];
} Entry;

extern Entry D_800B9D0C[];
extern Entry D_800B9E5C[];
extern Entry D_800B9FE4[];
extern Entry D_800BA16C[];
extern s32 D_800579BC[];
extern u8 D_800B61B5;
extern s8 D_800B95AD[][21];

void func_8001142C(s32 arg0, s32 arg1, u8 arg2) {
    if (arg2 < 65 || arg2 >= 91) {
        return;
    }
    D_800B95AD[arg0][arg1] = D_800B61B5;
    switch (arg0) {
    case 0:
        D_800B9D0C[arg1].unk_00 = D_800579BC[arg2];
        return;
    case 1:
        D_800B9E5C[arg1].unk_00 = D_800579BC[arg2];
        return;
    case 2:
        D_800B9FE4[arg1].unk_00 = D_800579BC[arg2];
        return;
    case 3:
        D_800BA16C[arg1].unk_00 = D_800579BC[arg2];
        return;
    }
}
