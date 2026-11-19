typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;

typedef struct {
    /* 0x00 */ s32 y;
    /* 0x04 */ s32 u;
    /* 0x08 */ s32 v;
} Frame;

typedef struct {
    /* 0x000 */ u8 unk_000[0xC];
    /* 0x00C */ s32 width;
    /* 0x010 */ u8 unk_010[0xC0];
    /* 0x0D0 */ s32 unk_D0;
    /* 0x0D4 */ u8 unk_0D4[0x34];
    /* 0x108 */ s32 unk_108;
    /* 0x10C */ u8 unk_10C[0x48];
    /* 0x154 */ s16 unk_154[0x68];
    /* 0x224 */ s32 unk_224;
    /* 0x228 */ s32 unk_228;
    /* 0x22C */ s32 unk_22C;
    /* 0x230 */ s32 unk_230;
    /* 0x234 */ u8 unk_234[0x24];
    /* 0x258 */ Frame *unk_258;
    /* 0x25C */ Frame *unk_25C;
    /* 0x260 */ Frame *unk_260;
} Decoder;

extern s32 D_80086D50;
extern u8 D_800FC098[];

void func_8008F828(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 sp0;
    s32 sp4;
    s32 sp8;
    s32 spC;
    s32 stride;
    s32 i;
    s32 sp18;
    s32 sp1C;
    u8 *sp20;
    u8 *sp24;
    u8 *sp28;
    u8 *sp2C;
    u8 *dst;
    s16 *coef;
    u8 *clip;
    u8 *sp3C;
    u8 *sp40;

    sp0 = (u32)((Decoder *)arg0)->unk_108 / (u32)((Decoder *)arg0)->width;
    sp4 = (u32)((Decoder *)arg0)->unk_108 % (u32)((Decoder *)arg0)->width;
    if (arg1 < 4) {
        ((Decoder *)arg0)->unk_224 = arg2 >> 1;
        ((Decoder *)arg0)->unk_228 = arg3 >> 1;
        ((Decoder *)arg0)->unk_22C = arg2 & 1;
        ((Decoder *)arg0)->unk_230 = arg3 & 1;
        sp18 = ((Decoder *)arg0)->unk_260->y;
        if (((Decoder *)arg0)->unk_D0 == 3) {
            if (((Decoder *)arg0)->unk_258 != 0) {
                sp1C = ((Decoder *)arg0)->unk_258->y;
            }
        } else {
            if (((Decoder *)arg0)->unk_25C != 0) {
                sp1C = ((Decoder *)arg0)->unk_25C->y;
            }
        }
        stride = ((Decoder *)arg0)->width << 4;
        sp8 = sp0 << 4;
        spC = sp4 << 4;
        if (arg1 >= 2) {
            sp8 += 8;
        }
        if (arg1 % 2 != 0) {
            spC += 8;
        }
    } else {
        arg2 = arg2 / 2;
        arg3 = arg3 / 2;
        ((Decoder *)arg0)->unk_224 = arg2 >> 1;
        ((Decoder *)arg0)->unk_228 = arg3 >> 1;
        ((Decoder *)arg0)->unk_22C = arg2 & 1;
        ((Decoder *)arg0)->unk_230 = arg3 & 1;
        stride = ((Decoder *)arg0)->width << 3;
        sp8 = sp0 << 3;
        spC = sp4 << 3;
        if (arg1 == 5) {
            sp18 = ((Decoder *)arg0)->unk_260->u;
            if (((Decoder *)arg0)->unk_D0 == 3) {
                if (((Decoder *)arg0)->unk_258 != 0) {
                    sp1C = ((Decoder *)arg0)->unk_258->u;
                }
            } else {
                if (((Decoder *)arg0)->unk_25C != 0) {
                    sp1C = ((Decoder *)arg0)->unk_25C->u;
                }
            }
        } else {
            sp18 = ((Decoder *)arg0)->unk_260->v;
            if (((Decoder *)arg0)->unk_D0 == 3) {
                if (((Decoder *)arg0)->unk_258 != 0) {
                    sp1C = ((Decoder *)arg0)->unk_258->v;
                }
            } else {
                if (((Decoder *)arg0)->unk_25C != 0) {
                    sp1C = ((Decoder *)arg0)->unk_25C->v;
                }
            }
        }
    }
    dst = (u8 *)(sp8 * stride + sp18 + spC);
    sp20 = (u8 *)((sp8 + ((Decoder *)arg0)->unk_228) * stride + sp1C + spC + ((Decoder *)arg0)->unk_224);
    coef = ((Decoder *)arg0)->unk_154;
    if (((Decoder *)arg0)->unk_230 == 0 && ((Decoder *)arg0)->unk_22C == 0) {
        clip = D_800FC098;
        if (arg4 == 0) {
            for (i = 0; i < 4; i++) {
                dst[0] = clip[sp20[0] + coef[0]];
                dst[1] = clip[sp20[1] + coef[1]];
                dst[2] = clip[sp20[2] + coef[2]];
                dst[3] = clip[sp20[3] + coef[3]];
                dst[4] = clip[sp20[4] + coef[4]];
                dst[5] = clip[sp20[5] + coef[5]];
                dst[6] = clip[sp20[6] + coef[6]];
                dst[7] = clip[sp20[7] + coef[7]];
                dst += stride;
                sp20 += stride;
                dst[0] = clip[sp20[0] + coef[8]];
                dst[1] = clip[sp20[1] + coef[9]];
                dst[2] = clip[sp20[2] + coef[10]];
                dst[3] = clip[sp20[3] + coef[11]];
                dst[4] = clip[sp20[4] + coef[12]];
                dst[5] = clip[sp20[5] + coef[13]];
                dst[6] = clip[sp20[6] + coef[14]];
                dst[7] = clip[sp20[7] + coef[15]];
                coef += 16;
                dst += stride;
                sp20 += stride;
            }
        } else {
            if ((((Decoder *)arg0)->unk_224 & 1) != 0) {
                for (i = 0; i < 4; i++) {
                    dst[0] = sp20[0];
                    dst[1] = sp20[1];
                    dst[2] = sp20[2];
                    dst[3] = sp20[3];
                    dst[4] = sp20[4];
                    dst[5] = sp20[5];
                    dst[6] = sp20[6];
                    dst[7] = sp20[7];
                    dst += stride;
                    sp20 += stride;
                    dst[0] = sp20[0];
                    dst[1] = sp20[1];
                    dst[2] = sp20[2];
                    dst[3] = sp20[3];
                    dst[4] = sp20[4];
                    dst[5] = sp20[5];
                    dst[6] = sp20[6];
                    dst[7] = sp20[7];
                    dst += stride;
                    sp20 += stride;
                }
            } else {
                if ((((Decoder *)arg0)->unk_224 & 2) != 0) {
                    sp3C = sp20;
                    sp40 = dst;
                    stride = stride >> 1;
                    for (i = 0; i < 4; i++) {
                        *(s16 *)sp40 = *(u16 *)sp3C;
                        *(s16 *)(sp40 + 2) = *(u16 *)(sp3C + 2);
                        *(s16 *)(sp40 + 4) = *(u16 *)(sp3C + 4);
                        *(s16 *)(sp40 + 6) = *(u16 *)(sp3C + 6);
                        sp40 += stride * 2;
                        sp3C += stride * 2;
                        *(s16 *)sp40 = *(u16 *)sp3C;
                        *(s16 *)(sp40 + 2) = *(u16 *)(sp3C + 2);
                        *(s16 *)(sp40 + 4) = *(u16 *)(sp3C + 4);
                        *(s16 *)(sp40 + 6) = *(u16 *)(sp3C + 6);
                        sp40 += stride * 2;
                        sp3C += stride * 2;
                    }
                } else {
                    sp40 = sp20;
                    sp3C = dst;
                    stride = stride >> 2;
                    for (i = 0; i < 4; i++) {
                        *(s32 *)sp3C = *(s32 *)sp40;
                        *(s32 *)(sp3C + 4) = *(s32 *)(sp40 + 4);
                        sp3C += stride * 4;
                        sp40 += stride * 4;
                        *(s32 *)sp3C = *(s32 *)sp40;
                        *(s32 *)(sp3C + 4) = *(s32 *)(sp40 + 4);
                        sp3C += stride * 4;
                        sp40 += stride * 4;
                    }
                }
            }
        }
        return;
    }
    sp40 = D_800FC098;
    sp24 = sp20 + ((Decoder *)arg0)->unk_22C + ((Decoder *)arg0)->unk_230 * stride;
    if (((Decoder *)arg0)->unk_22C == 0 || (((Decoder *)arg0)->unk_230 == 0 || D_80086D50 == 0)) {
        if (arg4 == 0) {
            for (i = 0; i < 4; i++) {
                dst[0] = sp40[((sp20[0] + sp24[0] + 1) >> 1) + coef[0]];
                dst[1] = sp40[((sp20[1] + sp24[1] + 1) >> 1) + coef[1]];
                dst[2] = sp40[((sp20[2] + sp24[2] + 1) >> 1) + coef[2]];
                dst[3] = sp40[((sp20[3] + sp24[3] + 1) >> 1) + coef[3]];
                dst[4] = sp40[((sp20[4] + sp24[4] + 1) >> 1) + coef[4]];
                dst[5] = sp40[((sp20[5] + sp24[5] + 1) >> 1) + coef[5]];
                dst[6] = sp40[((sp20[6] + sp24[6] + 1) >> 1) + coef[6]];
                dst[7] = sp40[((sp20[7] + sp24[7] + 1) >> 1) + coef[7]];
                dst += stride;
                sp20 += stride;
                sp24 += stride;
                dst[0] = sp40[((sp20[0] + sp24[0] + 1) >> 1) + coef[8]];
                dst[1] = sp40[((sp20[1] + sp24[1] + 1) >> 1) + coef[9]];
                dst[2] = sp40[((sp20[2] + sp24[2] + 1) >> 1) + coef[10]];
                dst[3] = sp40[((sp20[3] + sp24[3] + 1) >> 1) + coef[11]];
                dst[4] = sp40[((sp20[4] + sp24[4] + 1) >> 1) + coef[12]];
                dst[5] = sp40[((sp20[5] + sp24[5] + 1) >> 1) + coef[13]];
                dst[6] = sp40[((sp20[6] + sp24[6] + 1) >> 1) + coef[14]];
                dst[7] = sp40[((sp20[7] + sp24[7] + 1) >> 1) + coef[15]];
                coef += 16;
                dst += stride;
                sp20 += stride;
                sp24 += stride;
            }
        } else {
            for (i = 0; i < 8; i++) {
                dst[0] = (sp20[0] + sp24[0] + 1) >> 1;
                dst[1] = (sp20[1] + sp24[1] + 1) >> 1;
                dst[2] = (sp20[2] + sp24[2] + 1) >> 1;
                dst[3] = (sp20[3] + sp24[3] + 1) >> 1;
                dst[4] = (sp20[4] + sp24[4] + 1) >> 1;
                dst[5] = (sp20[5] + sp24[5] + 1) >> 1;
                dst[6] = (sp20[6] + sp24[6] + 1) >> 1;
                dst[7] = (sp20[7] + sp24[7] + 1) >> 1;
                dst += stride;
                sp20 += stride;
                sp24 += stride;
            }
        }
        return;
    }
    sp28 = sp20 + ((Decoder *)arg0)->unk_22C;
    sp2C = sp20 + ((Decoder *)arg0)->unk_230 * stride;
    if (arg4 == 0) {
        for (i = 0; i < 4; i++) {
            dst[0] = sp40[((sp20[0] + sp24[0] + sp28[0] + sp2C[0] + 2) >> 2) + coef[0]];
            dst[1] = sp40[((sp20[1] + sp24[1] + sp28[1] + sp2C[1] + 2) >> 2) + coef[1]];
            dst[2] = sp40[((sp20[2] + sp24[2] + sp28[2] + sp2C[2] + 2) >> 2) + coef[2]];
            dst[3] = sp40[((sp20[3] + sp24[3] + sp28[3] + sp2C[3] + 2) >> 2) + coef[3]];
            dst[4] = sp40[((sp20[4] + sp24[4] + sp28[4] + sp2C[4] + 2) >> 2) + coef[4]];
            dst[5] = sp40[((sp20[5] + sp24[5] + sp28[5] + sp2C[5] + 2) >> 2) + coef[5]];
            dst[6] = sp40[((sp20[6] + sp24[6] + sp28[6] + sp2C[6] + 2) >> 2) + coef[6]];
            dst[7] = sp40[((sp20[7] + sp24[7] + sp28[7] + sp2C[7] + 2) >> 2) + coef[7]];
            dst += stride;
            sp20 += stride;
            sp24 += stride;
            sp28 += stride;
            sp2C += stride;
            dst[0] = sp40[((sp20[0] + sp24[0] + sp28[0] + sp2C[0] + 2) >> 2) + coef[8]];
            dst[1] = sp40[((sp20[1] + sp24[1] + sp28[1] + sp2C[1] + 2) >> 2) + coef[9]];
            dst[2] = sp40[((sp20[2] + sp24[2] + sp28[2] + sp2C[2] + 2) >> 2) + coef[10]];
            dst[3] = sp40[((sp20[3] + sp24[3] + sp28[3] + sp2C[3] + 2) >> 2) + coef[11]];
            dst[4] = sp40[((sp20[4] + sp24[4] + sp28[4] + sp2C[4] + 2) >> 2) + coef[12]];
            dst[5] = sp40[((sp20[5] + sp24[5] + sp28[5] + sp2C[5] + 2) >> 2) + coef[13]];
            dst[6] = sp40[((sp20[6] + sp24[6] + sp28[6] + sp2C[6] + 2) >> 2) + coef[14]];
            dst[7] = sp40[((sp20[7] + sp24[7] + sp28[7] + sp2C[7] + 2) >> 2) + coef[15]];
            coef += 16;
            dst += stride;
            sp20 += stride;
            sp24 += stride;
            sp28 += stride;
            sp2C += stride;
        }
        return;
    }
    i = 0;
    while (i < 8) {
        dst[0] = (sp20[0] + sp24[0] + sp28[0] + sp2C[0] + 2) >> 2;
        dst[1] = (sp20[1] + sp24[1] + sp28[1] + sp2C[1] + 2) >> 2;
        dst[2] = (sp20[2] + sp24[2] + sp28[2] + sp2C[2] + 2) >> 2;
        dst[3] = (sp20[3] + sp24[3] + sp28[3] + sp2C[3] + 2) >> 2;
        dst[4] = (sp20[4] + sp24[4] + sp28[4] + sp2C[4] + 2) >> 2;
        dst[5] = (sp20[5] + sp24[5] + sp28[5] + sp2C[5] + 2) >> 2;
        dst[6] = (sp20[6] + sp24[6] + sp28[6] + sp2C[6] + 2) >> 2;
        dst[7] = (sp20[7] + sp24[7] + sp28[7] + sp2C[7] + 2) >> 2;
        dst += stride;
        sp20 += stride;
        sp24 += stride;
        sp28 += stride;
        sp2C += stride;
        i++;
    }
}
