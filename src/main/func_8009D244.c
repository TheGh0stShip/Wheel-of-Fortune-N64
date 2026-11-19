typedef unsigned char u8;
typedef signed int s32;

typedef struct {
    /* 0x000 */ u8 unk_000[0x1F4];
    /* 0x1F4 */ s32 unk_1F4;
    /* 0x1F8 */ u8 unk_1F8[0x50];
    /* 0x248 */ s32 unk_248;
} Obj;

extern s32 D_801033F8;
extern s32 D_8010346C;
extern Obj *D_80107884;
s32 func_80089B10(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_800A4E58(s32 arg0);

s32 func_8009D244(void) {
    s32 start;

    start = D_80107884->unk_248;
    while (start == D_80107884->unk_248) {
        func_80089B10(0, (s32)D_80107884, 0, (s32)&D_801033F8);
    }
    if (D_80107884->unk_1F4 != 0) {
        func_800A4E58(D_8010346C);
        return 1;
    }
    return 0;
}
