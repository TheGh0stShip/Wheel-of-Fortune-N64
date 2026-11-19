typedef unsigned char u8;
typedef signed int s32;

typedef struct {
    /* 0x00 */ u8 pad0[0x4];
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 rows;
    /* 0x14 */ s32 cols;
    /* 0x18 */ s32 sel;
} Grid;

extern s32 D_80001574;
void func_80009F38(void *arg0);
void func_800226BC(s32 arg0, s32 arg1, s32 arg2);

void func_80022784(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 sel;
    s32 i;

    sel = ((Grid *)arg2)->sel;
    if (sel < 0 || sel >= ((Grid *)arg2)->rows) {
        func_80009F38(&D_80001574);
    }
    func_800226BC(((Grid *)arg2)->unk_04 * 40 + arg1, ((Grid *)arg2)->unk_08, arg3 * 2);
    for (i = 0; i < ((Grid *)arg2)->rows * ((Grid *)arg2)->cols; i += ((Grid *)arg2)->cols) {
        if (arg3 != 0 && i == sel * ((Grid *)arg2)->cols) {
            func_800226BC((((Grid *)arg2)->unk_0C + i) * 40 + arg1, ((Grid *)arg2)->cols, 1);
        } else if (arg3 == 0 && i == sel * ((Grid *)arg2)->cols && ((Grid *)arg2)->rows >= 2) {
            func_800226BC((((Grid *)arg2)->unk_0C + i) * 40 + arg1, ((Grid *)arg2)->cols, 2);
        } else {
            func_800226BC((((Grid *)arg2)->unk_0C + i) * 40 + arg1, ((Grid *)arg2)->cols, 0);
        }
    }
}
