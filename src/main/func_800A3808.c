typedef unsigned char u8;
typedef signed int s32;

typedef struct {
    /* 0x000 */ u8 unk_000[0x204];
    /* 0x204 */ s32 unk_204;
    /* 0x208 */ s32 unk_208;
} State;

s32 func_800A38F8(s32 arg0);
s32 func_800A4A18(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

s32 func_800A3808(s32 arg0, s32 arg1) {
    s32 count;

    count = func_800A4A18(arg0, 1, 4, ((State *)arg1)->unk_208);
    *(s32 *)arg0 = *(s32 *)arg0;
    if (count < 4) {
        ((State *)arg1)->unk_204 = 1;
        return 1;
    }
    if ((*(s32 *)arg0 & -512) != 0) {
        *(s32 *)arg0 = func_800A38F8(((State *)arg1)->unk_208);
        if (*(s32 *)arg0 == -1) {
            ((State *)arg1)->unk_204 = 1;
            return 0;
        }
    }
    return 0;
}
