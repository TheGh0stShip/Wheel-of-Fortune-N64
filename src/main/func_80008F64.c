typedef unsigned char u8;
typedef signed int s32;

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[0x14];
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
} Entry;

extern Entry D_800B39B8[];
extern s32 D_80000798;
extern s32 D_800BEDA8;
s32 func_80009900(s32 arg0, s32 arg1);
void func_80009AE0(s32 arg0, s32 arg1);

void func_80008F64(void) {
    if (D_800B39B8[D_800BEDA8].unk_00 == -10000) {
        D_800B39B8[D_800BEDA8].unk_00 = -1;
        func_80009900((s32)D_800B39B8[D_800BEDA8].unk_04, (s32)&D_80000798);
        D_800B39B8[D_800BEDA8].unk_18 = 0;
        D_800B39B8[D_800BEDA8].unk_1C = 1;
        return;
    }
    D_800B39B8[D_800BEDA8].unk_00 = D_800B39B8[D_800BEDA8].unk_00 * -1;
    func_80009AE0((s32)D_800B39B8[D_800BEDA8].unk_04, D_800B39B8[D_800BEDA8].unk_00);
    D_800B39B8[D_800BEDA8].unk_18 = 0;
    D_800B39B8[D_800BEDA8].unk_1C = 1;
}
