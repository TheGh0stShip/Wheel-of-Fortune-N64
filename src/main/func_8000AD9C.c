typedef unsigned char u8;
typedef signed int s32;

typedef struct {
    /* 0x00 */ u8 unk_00[0x18];
    /* 0x18 */ s32 unk_18;
} Obj;

extern s32 D_800009D0;
void func_80009F38(void *arg0);

void func_8000AD9C(s32 arg0) {
    if (arg0 == 0) {
        func_80009F38(&D_800009D0);
    }
    ((Obj *)arg0)->unk_18 = 0;
}
