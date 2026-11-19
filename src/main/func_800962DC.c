typedef unsigned char u8;
typedef signed int s32;

typedef struct {
    /* 0x00 */ u8 unk_00[0x10];
    /* 0x10 */ s32 flags;
} Item;

typedef struct {
    /* 0x000 */ u8 unk_000[0xD0];
    /* 0x0D0 */ s32 unk_D0;
    /* 0x0D4 */ u8 unk_D4[0x184];
    /* 0x258 */ Item *unk_258;
    /* 0x25C */ Item *unk_25C;
    /* 0x260 */ Item *unk_260;
} Menu;

void func_8009CAD8(s32 arg0, s32 arg1);
void func_8009D300(s32 arg0);

void func_800962DC(s32 arg0, s32 arg1) {
    func_8009D300(arg0);
    if (((Menu *)arg0)->unk_D0 == 1 || ((Menu *)arg0)->unk_D0 == 2) {
        if (((Menu *)arg0)->unk_25C == 0) {
            ((Menu *)arg0)->unk_25C = ((Menu *)arg0)->unk_260;
            ((Menu *)arg0)->unk_25C->flags |= 4;
        } else {
            if (((Menu *)arg0)->unk_258 != 0) {
                ((Menu *)arg0)->unk_258->flags &= -3;
            }
            ((Menu *)arg0)->unk_258 = ((Menu *)arg0)->unk_25C;
            ((Menu *)arg0)->unk_258->flags &= -5;
            ((Menu *)arg0)->unk_258->flags |= 2;
            ((Menu *)arg0)->unk_25C = ((Menu *)arg0)->unk_260;
            ((Menu *)arg0)->unk_25C->flags |= 4;
            ((Menu *)arg0)->unk_260 = ((Menu *)arg0)->unk_258;
            func_8009CAD8(arg0, arg1);
        }
        return;
    }
    func_8009CAD8(arg0, arg1);
}
