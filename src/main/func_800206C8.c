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
extern s32 *D_800B81E4;
extern s32 D_800B96A4;
extern s16 *D_800B998C;
extern u8 D_800BEF60[][0x1E480];
s32 func_8003FF78(void *arg0);

void func_800206C8(s32 arg0) {
    s32 diff;
    s32 i;
    s32 j;
    s32 row;
    s32 n;
    u16 *src;
    s16 *dst;
    s32 *mask;
    s32 bits0;
    s32 bits1;
    s32 base;

    base = 0x2000000;
    diff = func_8003FF78(D_800BEF5C[D_800B61A0].unk_04 + 0xAC00);
    diff = diff - func_8003FF78(D_800BEF60[D_800B61A0]);
    src = (u16 *)arg0;
    dst = (s16 *)(D_800BEF5C[D_800B61A0].unk_04 + 0xAC00);
    if (D_800B96A4 != 0) {
        dst = D_800B998C;
        mask = D_800B81E4;
        n = 4032;
        row = 126;
        for (i = 0; i < 64; i++) {
            bits0 = mask[row];
            bits1 = mask[row + 1];
            for (j = 0; j < 32; j++) {
                if (bits0 & 0x80000000) {
                    dst[i * 32 + j] = src[n];
                } else {
                    dst[i * 32 + j] = 0;
                }
                if (bits1 & 0x80000000) {
                    dst[i * 32 + j + 0x800] = src[n + 32];
                } else {
                    dst[i * 32 + j + 0x800] = 0;
                }
                bits0 <<= 1;
                bits1 <<= 1;
                n++;
            }
            row -= 2;
            n -= 96;
        }
        D_800B998C += 0x1000;
        D_800B81E4 += 128;
        return;
    }
    dst = (s16 *)(D_800BEF5C[D_800B61A0].unk_04 + 0x19C00);
    row = 0;
    n = 0;
    mask = D_800B81E4;
    for (i = 0; i < 64; i++) {
        bits0 = mask[row++];
        bits1 = mask[row++];
        for (j = 0; j < 32; j++) {
            if (bits0 & 0x80000000) {
                dst[i * 32 + j] = src[n];
            } else {
                dst[i * 32 + j] = 0;
            }
            if (bits1 & 0x80000000) {
                dst[i * 32 + j + 0x800] = src[n + 32];
            } else {
                dst[i * 32 + j + 0x800] = 0;
            }
            bits0 <<= 1;
            bits1 <<= 1;
            n++;
        }
        n += 32;
    }
    D_800B81E4 += 128;
}
