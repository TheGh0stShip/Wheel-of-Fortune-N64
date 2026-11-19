typedef unsigned char u8;
typedef signed int s32;

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[0x24];
} Slot;

extern Slot D_8005ADE0[][7];

void func_80029BFC(s32 arg0) {
    s32 i;

    for (i = 0; i < 7; i++) {
        D_8005ADE0[arg0][i].unk_00 = 1;
    }
}
