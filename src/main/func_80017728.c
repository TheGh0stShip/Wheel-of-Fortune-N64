typedef unsigned char u8;
typedef signed char s8;
typedef signed int s32;

typedef struct {
    /* 0x000 */ s32 unk_00;
    /* 0x004 */ u8 pad4[0x110];
} Entry;

extern Entry D_800B9998[];
extern s32 D_800BCA00;
extern s32 D_800FB808;

s32 func_80017728(void) {
    s8 pad0;

    if (D_800B9998[D_800FB808].unk_00 != 0 && D_800BCA00 == 0) {
        return 0;
    }
    return 1;
}
