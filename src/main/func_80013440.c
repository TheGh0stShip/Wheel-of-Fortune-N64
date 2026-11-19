typedef unsigned char u8;
typedef signed int s32;

typedef struct {
    /* 0x00 */ u8 unk_00[0x4];
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
} Blink;

extern s32 D_800B96B4;

s32 func_80013440(s32 arg0) {
    s32 result;

    result = ((Blink *)arg0)->unk_10;
    if (((Blink *)arg0)->unk_04 != 0) {
        if (((Blink *)arg0)->unk_0C > ((Blink *)arg0)->unk_08 / 2) {
            result = ((Blink *)arg0)->unk_14;
        }
        ((Blink *)arg0)->unk_0C = ((Blink *)arg0)->unk_0C - D_800B96B4;
        if (((Blink *)arg0)->unk_0C < 0) {
            ((Blink *)arg0)->unk_0C = ((Blink *)arg0)->unk_08;
        }
    }
    return result;
}
