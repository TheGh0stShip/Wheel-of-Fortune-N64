#include "wof.h"

typedef struct {
    /* 0x00 */ u8 *planes[3];
} Planes;

typedef struct {
    /* 0x000 */ u8 unk_000[0xC];
    /* 0x00C */ s32 width;
    /* 0x010 */ u8 unk_010[0xF8];
    /* 0x108 */ s32 block;
    /* 0x10C */ u8 unk_10C[0x48];
    /* 0x154 */ s16 coeffs[0x86];
    /* 0x260 */ Planes *out;
} Decoder;

void func_8008F3AC(s32 arg0, s32 arg1) {
    s32 row;
    s32 col;
    s32 y;
    s32 x;
    s32 stride;
    s32 i;
    u8 *dst;
    s16 *src;
    u8 *table;

    row = (u32)((Decoder *)arg0)->block / (u32)((Decoder *)arg0)->width;
    col = (u32)((Decoder *)arg0)->block % (u32)((Decoder *)arg0)->width;
    if (arg1 < 4) {
        y = row * 16;
        x = col * 16;
        if (arg1 >= 2) {
            y = y + 8;
        }
        if (arg1 % 2 != 0) {
            x = x + 8;
        }
        dst = ((Decoder *)arg0)->out->planes[0];
        stride = ((Decoder *)arg0)->width * 16;
    } else if (arg1 == 5) {
        dst = ((Decoder *)arg0)->out->planes[1];
        stride = ((Decoder *)arg0)->width * 8;
        y = row * 8;
        x = col * 8;
    } else {
        dst = ((Decoder *)arg0)->out->planes[2];
        stride = ((Decoder *)arg0)->width * 8;
        y = row * 8;
        x = col * 8;
    }
    src = ((Decoder *)arg0)->coeffs;
    table = D_800FC098;
    dst = dst + (y * stride + x);
    for (i = 0; i < 4; i++, src += 16, dst += stride) {
        dst[0] = table[src[0]];
        dst[1] = table[src[1]];
        dst[2] = table[src[2]];
        dst[3] = table[src[3]];
        dst[4] = table[src[4]];
        dst[5] = table[src[5]];
        dst[6] = table[src[6]];
        dst[7] = table[src[7]];
        dst = dst + stride;
        dst[0] = table[src[8]];
        dst[1] = table[src[9]];
        dst[2] = table[src[10]];
        dst[3] = table[src[11]];
        dst[4] = table[src[12]];
        dst[5] = table[src[13]];
        dst[6] = table[src[14]];
        dst[7] = table[src[15]];
    }
}
