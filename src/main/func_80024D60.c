typedef unsigned char u8;
typedef signed int s32;

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
} Preset;

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 pad04[0xE0];
    /* 0xE4 */ s32 unk_E4;
    /* 0xE8 */ s32 unk_E8;
    /* 0xEC */ s32 unk_EC;
    /* 0xF0 */ s32 unk_F0;
    /* 0xF4 */ s32 unk_F4;
    /* 0xF8 */ s32 unk_F8;
    /* 0xFC */ u8 padFC[0x18];
} Slot;

extern Preset D_8005A3E4[];
extern Slot D_800B99A8[];

void func_80024D60(s32 arg0) {
    D_800B99A8[arg0].unk_F8 = D_8005A3E4[D_800B99A8[arg0].unk_00].unk_14;
    D_800B99A8[arg0].unk_E4 = D_8005A3E4[D_800B99A8[arg0].unk_00].unk_00;
    D_800B99A8[arg0].unk_E8 = D_8005A3E4[D_800B99A8[arg0].unk_00].unk_04;
    D_800B99A8[arg0].unk_EC = D_8005A3E4[D_800B99A8[arg0].unk_00].unk_08;
    D_800B99A8[arg0].unk_F0 = D_8005A3E4[D_800B99A8[arg0].unk_00].unk_0C;
    D_800B99A8[arg0].unk_F4 = D_8005A3E4[D_800B99A8[arg0].unk_00].unk_10;
}
