typedef unsigned char u8;
typedef signed int s32;

typedef struct {
    /* 0x00 */ u8 unk_00[0xC];
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ u8 unk_10[0x4];
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ s32 count;
    /* 0x1C */ s32 items[5];
} Obj;

extern s32 D_800008FC;
extern s32 D_80000918;
extern s32 D_80000938;
void func_80009F38(s32 *arg0);

void func_8000AAB0(s32 arg0, s32 arg1, s32 arg2) {
    if (arg0 == 0) {
        func_80009F38(&D_800008FC);
        return;
    }
    if (arg1 >= 53) {
        func_80009F38(&D_80000918);
        return;
    }
    if (((Obj *)arg0)->count < 5) {
        ((Obj *)arg0)->items[((Obj *)arg0)->count] = arg1;
        ((Obj *)arg0)->count++;
        if (arg2 != 0) {
            ((Obj *)arg0)->unk_14 = 0;
            ((Obj *)arg0)->unk_0C = 0;
        }
        return;
    }
    func_80009F38(&D_80000938);
}
