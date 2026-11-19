typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;

typedef struct {
    /* 0x00000 */ u8 unk_00[0x4];
    /* 0x00004 */ u8 unk_04[0x1E47C];
} Frame;

extern Frame D_800BEF5C[];
extern s32 D_800B61A0;

void func_8003143C(s32 arg0, s32 arg1) {
    s32 i;
    s32 j;
    s32 k;
    s32 pad0;
    u16 *src;
    s16 *dst;

    src = (u16 *)arg0;
    dst = (s16 *)(D_800BEF5C[D_800B61A0].unk_04 + 0x16C00);
    if (arg1 == -1) {
        for (i = 0; i < 96; i++) {
            k = 63;
            for (j = 0; j < 64; j++) {
                dst[i * 64 + j] = src[i * 64 + k];
                k--;
            }
        }
        return;
    }
    i = 0;
    while (i < 0x1800) {
        dst[i] = src[i];
        i++;
    }
}
