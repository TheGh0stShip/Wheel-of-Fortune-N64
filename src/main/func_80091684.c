typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;

typedef struct {
    /* 0x00 */ s32 plane[3];
} Frame;

typedef struct {
    /* 0x000 */ u8 pad0[0xC];
    /* 0x00C */ s32 stride;
    /* 0x010 */ u8 pad10[0xF8];
    /* 0x108 */ s32 pos;
    /* 0x10C */ u8 pad10C[0x48];
    /* 0x154 */ s16 block[132];
    /* 0x25C */ Frame *ref;
    /* 0x260 */ Frame *cur;
} Decoder;

extern s32 D_80086D50;
extern u8 D_800FC098[];

void func_80091684(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 sp0;
    s32 sp4;
    s32 sp8;
    s32 spC;
    s32 sp10;
    s32 i;
    s32 sp18;
    s32 sp1C;
    s32 sp20;
    s32 sp24;
    s32 sp28;
    s32 sp2C;
    u8 *sp30;
    u8 *sp34;
    u8 *sp38;
    u8 *sp3C;
    u8 *sp40;
    s16 *sp44;
    u8 *sp48;
    u8 *sp4C;
    u8 *sp50;

    sp0 = (u32)((Decoder *)arg0)->pos / (u32)((Decoder *)arg0)->stride;
    sp4 = (u32)((Decoder *)arg0)->pos % (u32)((Decoder *)arg0)->stride;
    if (arg1 < 4) {
        sp20 = arg2 >> 1;
        sp24 = arg3 >> 1;
        sp28 = arg2 & 1;
        sp2C = arg3 & 1;
        sp18 = ((Decoder *)arg0)->cur->plane[0];
        if (((Decoder *)arg0)->ref != 0) {
            sp1C = ((Decoder *)arg0)->ref->plane[0];
        }
        sp10 = ((Decoder *)arg0)->stride << 4;
        sp8 = sp0 << 4;
        spC = sp4 << 4;
        if (arg1 >= 2) {
            sp8 += 8;
        }
        if (arg1 % 2 != 0) {
            spC += 8;
        }
    } else {
        arg2 /= 2;
        arg3 /= 2;
        sp20 = arg2 >> 1;
        sp24 = arg3 >> 1;
        sp28 = arg2 & 1;
        sp2C = arg3 & 1;
        sp10 = ((Decoder *)arg0)->stride << 3;
        sp8 = sp0 << 3;
        spC = sp4 << 3;
        if (arg1 == 5) {
            sp18 = ((Decoder *)arg0)->cur->plane[1];
            if (((Decoder *)arg0)->ref != 0) {
                sp1C = ((Decoder *)arg0)->ref->plane[1];
            }
        } else {
            sp18 = ((Decoder *)arg0)->cur->plane[2];
            if (((Decoder *)arg0)->ref != 0) {
                sp1C = ((Decoder *)arg0)->ref->plane[2];
            }
        }
    }
    sp40 = (u8 *)(sp8 * sp10 + sp18 + spC);
    sp30 = (u8 *)((sp8 + sp24) * sp10 + sp1C + spC + sp20);
    sp44 = ((Decoder *)arg0)->block;
    if (sp28 == 0 && sp2C == 0) {
        sp48 = D_800FC098;
        if (arg4 == 0) {
            for (i = 0; i < 4; i++) {
                sp40[0] = sp48[sp30[0] + sp44[0]];
                sp40[1] = sp48[sp30[1] + sp44[1]];
                sp40[2] = sp48[sp30[2] + sp44[2]];
                sp40[3] = sp48[sp30[3] + sp44[3]];
                sp40[4] = sp48[sp30[4] + sp44[4]];
                sp40[5] = sp48[sp30[5] + sp44[5]];
                sp40[6] = sp48[sp30[6] + sp44[6]];
                sp40[7] = sp48[sp30[7] + sp44[7]];
                sp40 += sp10;
                sp30 += sp10;
                sp40[0] = sp48[sp30[0] + sp44[8]];
                sp40[1] = sp48[sp30[1] + sp44[9]];
                sp40[2] = sp48[sp30[2] + sp44[10]];
                sp40[3] = sp48[sp30[3] + sp44[11]];
                sp40[4] = sp48[sp30[4] + sp44[12]];
                sp40[5] = sp48[sp30[5] + sp44[13]];
                sp40[6] = sp48[sp30[6] + sp44[14]];
                sp40[7] = sp48[sp30[7] + sp44[15]];
                sp44 += 16;
                sp40 += sp10;
                sp30 += sp10;
            }
        } else if ((sp20 & 1) != 0) {
            for (i = 0; i < 4; i++) {
                sp40[0] = sp30[0];
                sp40[1] = sp30[1];
                sp40[2] = sp30[2];
                sp40[3] = sp30[3];
                sp40[4] = sp30[4];
                sp40[5] = sp30[5];
                sp40[6] = sp30[6];
                sp40[7] = sp30[7];
                sp40 += sp10;
                sp30 += sp10;
                sp40[0] = sp30[0];
                sp40[1] = sp30[1];
                sp40[2] = sp30[2];
                sp40[3] = sp30[3];
                sp40[4] = sp30[4];
                sp40[5] = sp30[5];
                sp40[6] = sp30[6];
                sp40[7] = sp30[7];
                sp40 += sp10;
                sp30 += sp10;
            }
        } else if ((sp20 & 2) != 0) {
            sp4C = sp30;
            sp50 = sp40;
            sp10 >>= 1;
            for (i = 0; i < 4; i++) {
                *(s16 *)sp50 = *(u16 *)sp4C;
                *(s16 *)(sp50 + 2) = *(u16 *)(sp4C + 2);
                *(s16 *)(sp50 + 4) = *(u16 *)(sp4C + 4);
                *(s16 *)(sp50 + 6) = *(u16 *)(sp4C + 6);
                sp50 += sp10 * 2;
                sp4C += sp10 * 2;
                *(s16 *)sp50 = *(u16 *)sp4C;
                *(s16 *)(sp50 + 2) = *(u16 *)(sp4C + 2);
                *(s16 *)(sp50 + 4) = *(u16 *)(sp4C + 4);
                *(s16 *)(sp50 + 6) = *(u16 *)(sp4C + 6);
                sp50 += sp10 * 2;
                sp4C += sp10 * 2;
            }
        } else {
            sp50 = sp30;
            sp4C = sp40;
            sp10 >>= 2;
            for (i = 0; i < 4; i++) {
                *(s32 *)sp4C = *(s32 *)sp50;
                *(s32 *)(sp4C + 4) = *(s32 *)(sp50 + 4);
                sp4C += sp10 * 4;
                sp50 += sp10 * 4;
                *(s32 *)sp4C = *(s32 *)sp50;
                *(s32 *)(sp4C + 4) = *(s32 *)(sp50 + 4);
                sp4C += sp10 * 4;
                sp50 += sp10 * 4;
            }
        }
        return;
    }
    sp50 = D_800FC098;
    sp34 = sp30 + sp28 + sp2C * sp10;
    if (D_80086D50 == 0) {
        if (arg4 == 0) {
            for (i = 0; i < 4; i++) {
                sp40[0] = sp50[((sp30[0] + sp34[0] + 1) >> 1) + sp44[0]];
                sp40[1] = sp50[((sp30[1] + sp34[1] + 1) >> 1) + sp44[1]];
                sp40[2] = sp50[((sp30[2] + sp34[2] + 1) >> 1) + sp44[2]];
                sp40[3] = sp50[((sp30[3] + sp34[3] + 1) >> 1) + sp44[3]];
                sp40[4] = sp50[((sp30[4] + sp34[4] + 1) >> 1) + sp44[4]];
                sp40[5] = sp50[((sp30[5] + sp34[5] + 1) >> 1) + sp44[5]];
                sp40[6] = sp50[((sp30[6] + sp34[6] + 1) >> 1) + sp44[6]];
                sp40[7] = sp50[((sp30[7] + sp34[7] + 1) >> 1) + sp44[7]];
                sp40 += sp10;
                sp30 += sp10;
                sp34 += sp10;
                sp40[0] = sp50[((sp30[0] + sp34[0] + 1) >> 1) + sp44[8]];
                sp40[1] = sp50[((sp30[1] + sp34[1] + 1) >> 1) + sp44[9]];
                sp40[2] = sp50[((sp30[2] + sp34[2] + 1) >> 1) + sp44[10]];
                sp40[3] = sp50[((sp30[3] + sp34[3] + 1) >> 1) + sp44[11]];
                sp40[4] = sp50[((sp30[4] + sp34[4] + 1) >> 1) + sp44[12]];
                sp40[5] = sp50[((sp30[5] + sp34[5] + 1) >> 1) + sp44[13]];
                sp40[6] = sp50[((sp30[6] + sp34[6] + 1) >> 1) + sp44[14]];
                sp40[7] = sp50[((sp30[7] + sp34[7] + 1) >> 1) + sp44[15]];
                sp44 += 16;
                sp40 += sp10;
                sp30 += sp10;
                sp34 += sp10;
            }
        } else {
            for (i = 0; i < 8; i++) {
                sp40[0] = (sp30[0] + sp34[0] + 1) >> 1;
                sp40[1] = (sp30[1] + sp34[1] + 1) >> 1;
                sp40[2] = (sp30[2] + sp34[2] + 1) >> 1;
                sp40[3] = (sp30[3] + sp34[3] + 1) >> 1;
                sp40[4] = (sp30[4] + sp34[4] + 1) >> 1;
                sp40[5] = (sp30[5] + sp34[5] + 1) >> 1;
                sp40[6] = (sp30[6] + sp34[6] + 1) >> 1;
                sp40[7] = (sp30[7] + sp34[7] + 1) >> 1;
                sp40 += sp10;
                sp30 += sp10;
                sp34 += sp10;
            }
        }
        return;
    }
    sp38 = sp30 + sp28;
    sp3C = sp30 + sp2C * sp10;
    if (arg4 == 0) {
        for (i = 0; i < 4; i++) {
            sp40[0] = sp50[((sp30[0] + sp34[0] + sp38[0] + sp3C[0] + 2) >> 2) + sp44[0]];
            sp40[1] = sp50[((sp30[1] + sp34[1] + sp38[1] + sp3C[1] + 2) >> 2) + sp44[1]];
            sp40[2] = sp50[((sp30[2] + sp34[2] + sp38[2] + sp3C[2] + 2) >> 2) + sp44[2]];
            sp40[3] = sp50[((sp30[3] + sp34[3] + sp38[3] + sp3C[3] + 2) >> 2) + sp44[3]];
            sp40[4] = sp50[((sp30[4] + sp34[4] + sp38[4] + sp3C[4] + 2) >> 2) + sp44[4]];
            sp40[5] = sp50[((sp30[5] + sp34[5] + sp38[5] + sp3C[5] + 2) >> 2) + sp44[5]];
            sp40[6] = sp50[((sp30[6] + sp34[6] + sp38[6] + sp3C[6] + 2) >> 2) + sp44[6]];
            sp40[7] = sp50[((sp30[7] + sp34[7] + sp38[7] + sp3C[7] + 2) >> 2) + sp44[7]];
            sp40 += sp10;
            sp30 += sp10;
            sp34 += sp10;
            sp38 += sp10;
            sp3C += sp10;
            sp40[0] = sp50[((sp30[0] + sp34[0] + sp38[0] + sp3C[0] + 2) >> 2) + sp44[8]];
            sp40[1] = sp50[((sp30[1] + sp34[1] + sp38[1] + sp3C[1] + 2) >> 2) + sp44[9]];
            sp40[2] = sp50[((sp30[2] + sp34[2] + sp38[2] + sp3C[2] + 2) >> 2) + sp44[10]];
            sp40[3] = sp50[((sp30[3] + sp34[3] + sp38[3] + sp3C[3] + 2) >> 2) + sp44[11]];
            sp40[4] = sp50[((sp30[4] + sp34[4] + sp38[4] + sp3C[4] + 2) >> 2) + sp44[12]];
            sp40[5] = sp50[((sp30[5] + sp34[5] + sp38[5] + sp3C[5] + 2) >> 2) + sp44[13]];
            sp40[6] = sp50[((sp30[6] + sp34[6] + sp38[6] + sp3C[6] + 2) >> 2) + sp44[14]];
            sp40[7] = sp50[((sp30[7] + sp34[7] + sp38[7] + sp3C[7] + 2) >> 2) + sp44[15]];
            sp44 += 16;
            sp40 += sp10;
            sp30 += sp10;
            sp34 += sp10;
            sp38 += sp10;
            sp3C += sp10;
        }
        return;
    }
    i = 0;
    while (i < 8) {
        sp40[0] = (sp30[0] + sp34[0] + sp38[0] + sp3C[0] + 2) >> 2;
        sp40[1] = (sp30[1] + sp34[1] + sp38[1] + sp3C[1] + 2) >> 2;
        sp40[2] = (sp30[2] + sp34[2] + sp38[2] + sp3C[2] + 2) >> 2;
        sp40[3] = (sp30[3] + sp34[3] + sp38[3] + sp3C[3] + 2) >> 2;
        sp40[4] = (sp30[4] + sp34[4] + sp38[4] + sp3C[4] + 2) >> 2;
        sp40[5] = (sp30[5] + sp34[5] + sp38[5] + sp3C[5] + 2) >> 2;
        sp40[6] = (sp30[6] + sp34[6] + sp38[6] + sp3C[6] + 2) >> 2;
        sp40[7] = (sp30[7] + sp34[7] + sp38[7] + sp3C[7] + 2) >> 2;
        sp40 += sp10;
        sp30 += sp10;
        sp34 += sp10;
        sp38 += sp10;
        sp3C += sp10;
        i++;
    }
}
