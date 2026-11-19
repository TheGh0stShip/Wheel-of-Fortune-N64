typedef unsigned char u8;
typedef signed short s16;
typedef signed int s32;
typedef unsigned int u32;

typedef struct {
    /* 0x00 */ u8 *planes[3];
} Frame;

typedef struct {
    /* 0x000 */ u8 unk_000[0xC];
    /* 0x00C */ u32 width;
    /* 0x010 */ u8 unk_010[0xF8];
    /* 0x108 */ u32 index;
    /* 0x10C */ u8 unk_10C[0x48];
    /* 0x154 */ s16 coefs[0x82];
    /* 0x258 */ Frame *ref0;
    /* 0x25C */ Frame *ref1;
    /* 0x260 */ Frame *cur;
} Decoder;

extern u8 D_800FC098[];

void func_800933BC(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    s32 row;
    s32 col;
    s32 y;
    s32 x;
    s32 stride;
    s32 i;
    u8 *sp18;
    u8 *sp1C;
    u8 *sp20;
    s32 sp24;
    s32 sp28;
    s32 sp2C;
    s32 sp30;
    s32 sp34;
    s32 sp38;
    s32 sp3C;
    s32 sp40;
    u8 *dst;
    u8 *src1;
    u8 *src2;
    s16 *coef;
    s32 sp54;
    s32 sp58;
    s32 sp5C;
    s32 sp60;
    u8 *clamp;

    sp1C = 0;
    sp20 = 0;
    row = ((Decoder *)arg0)->index / ((Decoder *)arg0)->width;
    col = ((Decoder *)arg0)->index % ((Decoder *)arg0)->width;
    if (arg1 < 4) {
        sp24 = arg2 >> 1;
        sp28 = arg3 >> 1;
        sp2C = arg2 & 1;
        sp30 = arg3 & 1;
        sp34 = arg4 >> 1;
        sp38 = arg5 >> 1;
        sp3C = arg4 & 1;
        sp40 = arg5 & 1;
        sp18 = ((Decoder *)arg0)->cur->planes[0];
        if (((Decoder *)arg0)->ref0 != 0) {
            sp1C = ((Decoder *)arg0)->ref0->planes[0];
        }
        if (((Decoder *)arg0)->ref1 != 0) {
            sp20 = ((Decoder *)arg0)->ref1->planes[0];
        }
        stride = ((Decoder *)arg0)->width << 4;
        y = row << 4;
        x = col << 4;
        if (arg1 >= 2) {
            y += 8;
        }
        if ((arg1 & 1) != 0) {
            x += 8;
        }
        sp5C = x + sp24;
        sp54 = y + sp28;
        sp60 = x + sp34;
        sp58 = y + sp38;
    } else {
        arg2 /= 2;
        arg3 /= 2;
        sp24 = arg2 >> 1;
        sp28 = arg3 >> 1;
        sp2C = arg2 & 1;
        sp30 = arg3 & 1;
        arg4 /= 2;
        arg5 /= 2;
        sp34 = arg4 >> 1;
        sp38 = arg5 >> 1;
        sp3C = arg4 & 1;
        sp40 = arg5 & 1;
        stride = ((Decoder *)arg0)->width << 3;
        y = row << 3;
        x = col << 3;
        sp5C = x + sp24;
        sp54 = y + sp28;
        sp60 = x + sp34;
        sp58 = y + sp38;
        if (arg1 == 5) {
            sp18 = ((Decoder *)arg0)->cur->planes[1];
            if (((Decoder *)arg0)->ref0 != 0) {
                sp1C = ((Decoder *)arg0)->ref0->planes[1];
            }
            if (((Decoder *)arg0)->ref1 != 0) {
                sp20 = ((Decoder *)arg0)->ref1->planes[1];
            }
        } else {
            sp18 = ((Decoder *)arg0)->cur->planes[2];
            if (((Decoder *)arg0)->ref0 != 0) {
                sp1C = ((Decoder *)arg0)->ref0->planes[2];
            }
            if (((Decoder *)arg0)->ref1 != 0) {
                sp20 = ((Decoder *)arg0)->ref1->planes[2];
            }
        }
    }
    dst = y * stride + sp18 + x;
    src1 = sp54 * stride + sp1C + sp5C;
    src2 = sp58 * stride + sp20 + sp60;
    coef = ((Decoder *)arg0)->coefs;
    clamp = D_800FC098;
    if (arg6 == 0) {
        for (i = 0; i < 4; i++) {
            dst[0] = clamp[((src1[0] + src2[0]) >> 1) + coef[0]];
            dst[1] = clamp[((src1[1] + src2[1]) >> 1) + coef[1]];
            dst[2] = clamp[((src1[2] + src2[2]) >> 1) + coef[2]];
            dst[3] = clamp[((src1[3] + src2[3]) >> 1) + coef[3]];
            dst[4] = clamp[((src1[4] + src2[4]) >> 1) + coef[4]];
            dst[5] = clamp[((src1[5] + src2[5]) >> 1) + coef[5]];
            dst[6] = clamp[((src1[6] + src2[6]) >> 1) + coef[6]];
            dst[7] = clamp[((src1[7] + src2[7]) >> 1) + coef[7]];
            dst += stride;
            src1 += stride;
            src2 += stride;
            dst[0] = clamp[((src1[0] + src2[0]) >> 1) + coef[8]];
            dst[1] = clamp[((src1[1] + src2[1]) >> 1) + coef[9]];
            dst[2] = clamp[((src1[2] + src2[2]) >> 1) + coef[10]];
            dst[3] = clamp[((src1[3] + src2[3]) >> 1) + coef[11]];
            dst[4] = clamp[((src1[4] + src2[4]) >> 1) + coef[12]];
            dst[5] = clamp[((src1[5] + src2[5]) >> 1) + coef[13]];
            dst[6] = clamp[((src1[6] + src2[6]) >> 1) + coef[14]];
            dst[7] = clamp[((src1[7] + src2[7]) >> 1) + coef[15]];
            coef += 16;
            dst += stride;
            src1 += stride;
            src2 += stride;
        }
        return;
    }
    i = 0;
    while (i < 4) {
        dst[0] = (src1[0] + src2[0]) >> 1;
        dst[1] = (src1[1] + src2[1]) >> 1;
        dst[2] = (src1[2] + src2[2]) >> 1;
        dst[3] = (src1[3] + src2[3]) >> 1;
        dst[4] = (src1[4] + src2[4]) >> 1;
        dst[5] = (src1[5] + src2[5]) >> 1;
        dst[6] = (src1[6] + src2[6]) >> 1;
        dst[7] = (src1[7] + src2[7]) >> 1;
        dst += stride;
        src1 += stride;
        src2 += stride;
        dst[0] = (src1[0] + src2[0]) >> 1;
        dst[1] = (src1[1] + src2[1]) >> 1;
        dst[2] = (src1[2] + src2[2]) >> 1;
        dst[3] = (src1[3] + src2[3]) >> 1;
        dst[4] = (src1[4] + src2[4]) >> 1;
        dst[5] = (src1[5] + src2[5]) >> 1;
        dst[6] = (src1[6] + src2[6]) >> 1;
        dst[7] = (src1[7] + src2[7]) >> 1;
        dst += stride;
        src1 += stride;
        src2 += stride;
        i++;
    }
}
