typedef unsigned char u8;
typedef signed char s8;
typedef signed int s32;

typedef struct {
    /* 0x00 */ u8 pad0[0x4];
    /* 0x04 */ s32 pos;
    /* 0x08 */ u8 *data;
} Stream;

s32 func_800A4A18(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 i;
    s32 total;
    s8 *dst;

    dst = (s8 *)arg0;
    total = arg2 * arg1;
    for (i = 0; i < total; i++) {
        dst[i] = ((Stream *)arg3)->data[((Stream *)arg3)->pos++];
    }
    return arg2;
}
