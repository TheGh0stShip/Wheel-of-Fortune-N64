#include "wof.h"

typedef struct {
    /* 0x00 */ s32 y;
    /* 0x04 */ s32 u;
    /* 0x08 */ s32 v;
} PlaneAddrs;

typedef struct {
    /* 0x00 */ u8 *y;
    /* 0x04 */ u8 *u;
    /* 0x08 */ u8 *v;
} Planes;

typedef struct {
    /* 0x000 */ u8 unk_000[0xC];
    /* 0x00C */ s32 unk_00C;
    /* 0x010 */ u8 unk_010[0xC8];
    /* 0x0D8 */ s32 unk_0D8;
    /* 0x0DC */ u8 unk_0DC[0x8];
    /* 0x0E4 */ s32 unk_0E4;
    /* 0x0E8 */ u8 unk_0E8[0x20];
    /* 0x108 */ s32 unk_108;
    /* 0x10C */ s32 unk_10C;
    /* 0x110 */ u8 unk_110[0x28];
    /* 0x138 */ s32 unk_138;
    /* 0x13C */ s32 unk_13C;
    /* 0x140 */ u8 unk_140[0x4];
    /* 0x144 */ s32 unk_144;
    /* 0x148 */ s32 unk_148;
    /* 0x14C */ s32 unk_14C;
    /* 0x150 */ s32 unk_150;
    /* 0x154 */ u8 unk_154[0xEC];
    /* 0x240 */ s32 unk_240;
    /* 0x244 */ u8 unk_244[0x14];
    /* 0x258 */ PlaneAddrs *unk_258;
    /* 0x25C */ PlaneAddrs *unk_25C;
    /* 0x260 */ Planes *unk_260;
} Decoder;

void func_80094578(s32 arg0) {
    s32 stride;
    s32 halfStride;
    s32 row;
    s32 col;
    s32 y;
    s32 x;
    s32 i;
    s32 sp44;
    s32 sp48;
    s32 sp4C;
    s32 sp50;
    s32 sp54;
    s32 sp58;
    s32 sp5C;
    s32 sp60;
    s32 block;
    s32 sp68;
    s32 sp6C;
    s32 sp70;
    s32 sp74;
    s32 sp78;
    s32 sp7C;
    s32 sp80;
    s32 sp84;
    s32 sp88;
    s32 sp8C;
    s32 sp90;
    s32 sp94;
    u8 blkA[256];
    u8 blkA_u[64];
    u8 blkA_v[64];
    u8 blkB[256];
    u8 blkB_u[64];
    u8 blkB_v[64];
    s32 strideWords;
    s32 halfStrideWords;
    s32 halfX;
    s32 halfY;
    s32 sp3A8;
    u8 *sp3AC;
    u8 *sp3B0;
    u8 *sp3B4;
    u8 *sp3B8;
    u8 *sp3BC;
    u8 *sp3C0;

    sp44 = 0;
    sp48 = 0;
    sp4C = 0;
    sp50 = 0;
    sp54 = 0;
    sp58 = 0;
    sp5C = 0;
    sp60 = 0;
    sp68 = 0;
    sp6C = 0;
    sp80 = 0;
    sp84 = 0;
    sp88 = 0;
    sp8C = 0;
    sp90 = 0;
    sp94 = 0;
    sp3A8 = ((Decoder *)arg0)->unk_240;
    stride = ((Decoder *)arg0)->unk_00C << 4;
    halfStride = stride >> 1;
    strideWords = stride >> 2;
    halfStrideWords = halfStride >> 2;
    if (((Decoder *)arg0)->unk_0D8 != 0) {
        sp70 = ((Decoder *)arg0)->unk_144 << 1;
        sp74 = ((Decoder *)arg0)->unk_148 << 1;
    } else {
        sp70 = ((Decoder *)arg0)->unk_144;
        sp74 = ((Decoder *)arg0)->unk_148;
    }
    if (((Decoder *)arg0)->unk_0E4 != 0) {
        sp78 = ((Decoder *)arg0)->unk_14C << 1;
        sp7C = ((Decoder *)arg0)->unk_150 << 1;
    } else {
        sp78 = ((Decoder *)arg0)->unk_14C;
        sp7C = ((Decoder *)arg0)->unk_150;
    }
    if (((Decoder *)arg0)->unk_138 != 0) {
        sp68 = sp70 >> 1;
        sp6C = sp74 >> 1;
        sp44 = sp70 & 1;
        sp48 = sp74 & 1;
        sp70 = sp70 / 2;
        sp74 = sp74 / 2;
        sp88 = sp70 >> 1;
        sp8C = sp74 >> 1;
        sp4C = sp70 & 1;
        sp50 = sp74 & 1;
    }
    if (((Decoder *)arg0)->unk_13C != 0) {
        sp80 = sp78 >> 1;
        sp84 = sp7C >> 1;
        sp54 = sp78 & 1;
        sp58 = sp7C & 1;
        sp78 = sp78 / 2;
        sp7C = sp7C / 2;
        sp90 = sp78 >> 1;
        sp94 = sp7C >> 1;
        sp5C = sp78 & 1;
        sp60 = sp7C & 1;
    }
    block = ((Decoder *)arg0)->unk_10C + 1;
    while (block < ((Decoder *)arg0)->unk_108) {
        row = (u32)block / (u32)((Decoder *)arg0)->unk_00C;
        col = (u32)block % (u32)((Decoder *)arg0)->unk_00C;
        y = row << 4;
        x = col << 4;
        halfY = y / 2;
        halfX = x / 2;
        if (((Decoder *)arg0)->unk_138 != 0) {
            func_80095664(((Decoder *)arg0)->unk_258->y, (s32)blkA, y, x, stride, sp68, sp6C, sp44, sp48, 16);
            func_80095664(((Decoder *)arg0)->unk_258->u, (s32)blkA_u, halfY, halfX, halfStride, sp88, sp8C, sp4C, sp50, 8);
            func_80095664(((Decoder *)arg0)->unk_258->v, (s32)blkA_v, halfY, halfX, halfStride, sp88, sp8C, sp4C, sp50, 8);
        }
        if (((Decoder *)arg0)->unk_13C != 0) {
            func_80095664(((Decoder *)arg0)->unk_25C->y, (s32)blkB, y, x, stride, sp80, sp84, sp54, sp58, 16);
            func_80095664(((Decoder *)arg0)->unk_25C->u, (s32)blkB_u, halfY, halfX, halfStride, sp90, sp94, sp5C, sp60, 8);
            func_80095664(((Decoder *)arg0)->unk_25C->v, (s32)blkB_v, halfY, halfX, halfStride, sp90, sp94, sp5C, sp60, 8);
        }
        if (((Decoder *)arg0)->unk_138 != 0 && ((Decoder *)arg0)->unk_13C == 0) {
            sp3AC = ((Decoder *)arg0)->unk_260->y + y * stride + x;
            sp3B4 = blkA;
            i = 0;
            while (i < 16) {
                ((s32 *)sp3AC)[0] = ((s32 *)sp3B4)[0];
                ((s32 *)sp3AC)[1] = ((s32 *)sp3B4)[1];
                ((s32 *)sp3AC)[2] = ((s32 *)sp3B4)[2];
                ((s32 *)sp3AC)[3] = ((s32 *)sp3B4)[3];
                sp3AC += strideWords * 4;
                sp3B4 += 16;
                i++;
            }
            sp3AC = ((Decoder *)arg0)->unk_260->u + halfY * halfStride + halfX;
            sp3B0 = ((Decoder *)arg0)->unk_260->v + halfY * halfStride + halfX;
            sp3B4 = blkA_u;
            sp3B8 = blkA_v;
            i = 0;
            while (i < 8) {
                ((s32 *)sp3AC)[0] = ((s32 *)sp3B4)[0];
                ((s32 *)sp3AC)[1] = ((s32 *)sp3B4)[1];
                ((s32 *)sp3B0)[0] = ((s32 *)sp3B8)[0];
                ((s32 *)sp3B0)[1] = ((s32 *)sp3B8)[1];
                sp3AC += halfStrideWords * 4;
                sp3B0 += halfStrideWords * 4;
                sp3B4 += 8;
                sp3B8 += 8;
                i++;
            }
        } else if (((Decoder *)arg0)->unk_13C != 0 && ((Decoder *)arg0)->unk_138 == 0) {
            sp3B0 = ((Decoder *)arg0)->unk_260->y + y * stride + x;
            sp3B8 = blkB;
            i = 0;
            while (i < 16) {
                ((s32 *)sp3B0)[0] = ((s32 *)sp3B8)[0];
                ((s32 *)sp3B0)[1] = ((s32 *)sp3B8)[1];
                ((s32 *)sp3B0)[2] = ((s32 *)sp3B8)[2];
                ((s32 *)sp3B0)[3] = ((s32 *)sp3B8)[3];
                sp3B0 += strideWords * 4;
                sp3B8 += 16;
                i++;
            }
            sp3B0 = ((Decoder *)arg0)->unk_260->u + halfY * halfStride + halfX;
            sp3AC = ((Decoder *)arg0)->unk_260->v + halfY * halfStride + halfX;
            sp3B8 = blkB_u;
            sp3B4 = blkB_v;
            i = 0;
            while (i < 8) {
                ((s32 *)sp3B0)[0] = ((s32 *)sp3B8)[0];
                ((s32 *)sp3B0)[1] = ((s32 *)sp3B8)[1];
                ((s32 *)sp3AC)[0] = ((s32 *)sp3B4)[0];
                ((s32 *)sp3AC)[1] = ((s32 *)sp3B4)[1];
                sp3B0 += halfStrideWords * 4;
                sp3AC += halfStrideWords * 4;
                sp3B8 += 8;
                sp3B4 += 8;
                i++;
            }
        } else {
            sp3BC = ((Decoder *)arg0)->unk_260->y + y * stride + x;
            sp3B8 = blkA;
            sp3B4 = blkB;
            i = 0;
            while (i < 16) {
                sp3BC[0] = (sp3B8[0] + sp3B4[0]) >> 1;
                sp3BC[1] = (sp3B8[1] + sp3B4[1]) >> 1;
                sp3BC[2] = (sp3B8[2] + sp3B4[2]) >> 1;
                sp3BC[3] = (sp3B8[3] + sp3B4[3]) >> 1;
                sp3BC[4] = (sp3B8[4] + sp3B4[4]) >> 1;
                sp3BC[5] = (sp3B8[5] + sp3B4[5]) >> 1;
                sp3BC[6] = (sp3B8[6] + sp3B4[6]) >> 1;
                sp3BC[7] = (sp3B8[7] + sp3B4[7]) >> 1;
                sp3BC[8] = (sp3B8[8] + sp3B4[8]) >> 1;
                sp3BC[9] = (sp3B8[9] + sp3B4[9]) >> 1;
                sp3BC[10] = (sp3B8[10] + sp3B4[10]) >> 1;
                sp3BC[11] = (sp3B8[11] + sp3B4[11]) >> 1;
                sp3BC[12] = (sp3B8[12] + sp3B4[12]) >> 1;
                sp3BC[13] = (sp3B8[13] + sp3B4[13]) >> 1;
                sp3BC[14] = (sp3B8[14] + sp3B4[14]) >> 1;
                sp3BC[15] = (sp3B8[15] + sp3B4[15]) >> 1;
                sp3BC += stride;
                sp3B8 += 16;
                sp3B4 += 16;
                i++;
            }
            sp3BC = ((Decoder *)arg0)->unk_260->u + halfY * halfStride + halfX;
            sp3C0 = ((Decoder *)arg0)->unk_260->v + halfY * halfStride + halfX;
            sp3B8 = blkA_u;
            sp3B4 = blkB_u;
            sp3B0 = blkA_v;
            sp3AC = blkB_v;
            i = 0;
            while (i < 8) {
                sp3BC[0] = (sp3B8[0] + sp3B4[0]) >> 1;
                sp3BC[1] = (sp3B8[1] + sp3B4[1]) >> 1;
                sp3BC[2] = (sp3B8[2] + sp3B4[2]) >> 1;
                sp3BC[3] = (sp3B8[3] + sp3B4[3]) >> 1;
                sp3BC[4] = (sp3B8[4] + sp3B4[4]) >> 1;
                sp3BC[5] = (sp3B8[5] + sp3B4[5]) >> 1;
                sp3BC[6] = (sp3B8[6] + sp3B4[6]) >> 1;
                sp3BC[7] = (sp3B8[7] + sp3B4[7]) >> 1;
                sp3BC += halfStride;
                sp3B8 += 8;
                sp3B4 += 8;
                sp3C0[0] = (sp3B0[0] + sp3AC[0]) >> 1;
                sp3C0[1] = (sp3B0[1] + sp3AC[1]) >> 1;
                sp3C0[2] = (sp3B0[2] + sp3AC[2]) >> 1;
                sp3C0[3] = (sp3B0[3] + sp3AC[3]) >> 1;
                sp3C0[4] = (sp3B0[4] + sp3AC[4]) >> 1;
                sp3C0[5] = (sp3B0[5] + sp3AC[5]) >> 1;
                sp3C0[6] = (sp3B0[6] + sp3AC[6]) >> 1;
                sp3C0[7] = (sp3B0[7] + sp3AC[7]) >> 1;
                sp3C0 += halfStride;
                sp3B0 += 8;
                sp3AC += 8;
                i++;
            }
        }
        block++;
    }
}
