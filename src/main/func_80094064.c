#include "wof.h"
#include "mpeg/proto.h"

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
} Frame;

typedef struct {
    /* 0x000 */ u8 unk_000[0xC];
    /* 0x00C */ s32 unk_00C;
    /* 0x010 */ u8 unk_010[0xF8];
    /* 0x108 */ s32 unk_108;
    /* 0x10C */ s32 unk_10C;
    /* 0x110 */ u8 unk_110[0x34];
    /* 0x144 */ s32 unk_144;
    /* 0x148 */ s32 unk_148;
    /* 0x14C */ u8 unk_14C[0xF4];
    /* 0x240 */ s32 unk_240;
    /* 0x244 */ u8 unk_244[0x18];
    /* 0x25C */ Frame *unk_25C;
    /* 0x260 */ Frame *unk_260;
} Ctx;

void func_80094064(s32 arg0) {
    s32 sp0;
    s32 sp4;
    s32 sp8;
    s32 spC;
    s32 sp10;
    s32 sp14;
    s32 i;
    s32 block;
    s32 sp20;
    s32 sp24;
    s32 sp28;
    s32 sp2C;
    s32 *dst;
    s32 *src;
    s32 *dst2;
    s32 *src2;
    s32 sp40;

    sp40 = ((Ctx *)arg0)->unk_240;
    sp0 = ((Ctx *)arg0)->unk_00C << 4;
    sp4 = sp0 >> 1;
    sp20 = sp0 >> 2;
    sp24 = sp4 >> 2;
    block = ((Ctx *)arg0)->unk_10C + 1;
    for (; block < ((Ctx *)arg0)->unk_108; block++) {
        sp8 = (u32)block / (u32)((Ctx *)arg0)->unk_00C;
        spC = (u32)block % (u32)((Ctx *)arg0)->unk_00C;
        sp10 = sp8 << 4;
        sp14 = spC << 4;
        dst = (s32 *)(((Ctx *)arg0)->unk_260->unk_00 + sp10 * sp0 + sp14);
        src = (s32 *)(((Ctx *)arg0)->unk_25C->unk_00 + sp10 * sp0 + sp14);
        for (i = 0; i < 8; i++) {
            dst[0] = src[0];
            dst[1] = src[1];
            dst[2] = src[2];
            dst[3] = src[3];
            dst = dst + sp20;
            src = src + sp20;
            dst[0] = src[0];
            dst[1] = src[1];
            dst[2] = src[2];
            dst[3] = src[3];
            dst = dst + sp20;
            src = src + sp20;
        }
        sp28 = sp10 >> 1;
        sp2C = sp14 >> 1;
        dst = (s32 *)(((Ctx *)arg0)->unk_260->unk_04 + sp28 * sp4 + sp2C);
        src = (s32 *)(((Ctx *)arg0)->unk_25C->unk_04 + sp28 * sp4 + sp2C);
        dst2 = (s32 *)(((Ctx *)arg0)->unk_260->unk_08 + sp28 * sp4 + sp2C);
        src2 = (s32 *)(((Ctx *)arg0)->unk_25C->unk_08 + sp28 * sp4 + sp2C);
        for (i = 0; i < 4; i++) {
            dst[0] = src[0];
            dst[1] = src[1];
            dst2[0] = src2[0];
            dst2[1] = src2[1];
            dst = dst + sp24;
            src = src + sp24;
            dst2 = dst2 + sp24;
            src2 = src2 + sp24;
            dst[0] = src[0];
            dst[1] = src[1];
            dst2[0] = src2[0];
            dst2[1] = src2[1];
            dst = dst + sp24;
            src = src + sp24;
            dst2 = dst2 + sp24;
            src2 = src2 + sp24;
        }
    }
    ((Ctx *)arg0)->unk_144 = 0;
    ((Ctx *)arg0)->unk_148 = 0;
}
