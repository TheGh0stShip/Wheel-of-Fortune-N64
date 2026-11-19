typedef unsigned char u8;
typedef signed int s32;

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[0x110];
} Entry;

extern Entry D_800B9994[];
extern s32 D_800FB808;
void func_800133C8(void);
void func_80029BFC(s32 arg0);

void func_80017848(void) {
    s32 i;
    s32 max;

    max = 0;
    D_800FB808 = 0;
    for (i = 0; i < 3; i++) {
        if (D_800B9994[i].unk_00 > max) {
            max = D_800B9994[i].unk_00;
            D_800FB808 = i;
        }
    }
    func_800133C8();
    func_80029BFC(D_800FB808);
}
