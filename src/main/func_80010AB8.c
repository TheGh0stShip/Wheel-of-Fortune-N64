typedef unsigned char u8;
typedef signed int s32;

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ u8 unk_08[0xC];
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ u8 unk_18[0x4];
} Slot;

extern Slot D_800B9D0C[];
extern Slot D_800B9E5C[];
extern Slot D_800B9FE4[];
extern Slot D_800BA16C[];

void func_80010AB8(s32 arg0) {
    if (arg0 < 12) {
        if (D_800B9D0C[arg0].unk_14 == 0x1111AAFF) {
            D_800B9D0C[arg0].unk_00 = D_800B9D0C[arg0].unk_04;
            D_800B9D0C[arg0].unk_14 = -1;
        }
        if (D_800BA16C[arg0].unk_14 == 0x1111AAFF) {
            D_800BA16C[arg0].unk_00 = D_800BA16C[arg0].unk_04;
            D_800BA16C[arg0].unk_14 = -1;
        }
    }
    if (D_800B9E5C[arg0].unk_14 == 0x1111AAFF) {
        D_800B9E5C[arg0].unk_00 = D_800B9E5C[arg0].unk_04;
        D_800B9E5C[arg0].unk_14 = -1;
    }
    if (D_800B9FE4[arg0].unk_14 == 0x1111AAFF) {
        D_800B9FE4[arg0].unk_00 = D_800B9FE4[arg0].unk_04;
        D_800B9FE4[arg0].unk_14 = -1;
    }
}
