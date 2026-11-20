#include "wof.h"
#include "mpeg/proto.h"

typedef struct {
    /* 0x00 */ u16 unk_00;
    /* 0x02 */ u16 unk_02;
} Pair;

extern Pair *D_800FF2DC;
extern Pair *D_800FF2E0;
extern Pair *D_800FF2E4;

void func_800A2594(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 base;
    s32 u;
    s32 v;
    s16 *dst0;
    s16 *dst1;
    s32 src1;
    s32 x;
    s32 y;
    s32 pad0[2];
    s32 pad1;
    s32 sp2C;
    s32 sp30;
    s32 sp34;
    s32 sp38;
    s32 half;
    s32 i0;
    s32 i1;
    s32 i2;

    half = arg5 / 2;
    dst0 = (s16 *)arg3;
    dst1 = dst0 + half + half;
    src1 = arg0 + half + half;
    for (y = 0; y < arg4; y += 2) {
        for (x = 0; x < half; x++) {
            u = *(u8 *)arg1++;
            v = *(u8 *)arg2++;
            sp2C = D_800FF2CC[u];
            sp30 = D_800FF2D0[u];
            sp34 = D_800FF2D4[v];
            sp38 = D_800FF2D8[v];
            base = D_800FF2C8[*(u8 *)arg0++];
            i0 = base + sp2C;
            i1 = base + sp30 + sp34;
            i2 = base + sp38;
            *dst0++ = D_800FF2DC[i0].unk_02 | D_800FF2E0[i1].unk_02 | D_800FF2E4[i2].unk_02 | 1;
            base = D_800FF2C8[*(u8 *)arg0++];
            i0 = base + sp2C;
            i1 = base + sp30 + sp34;
            i2 = base + sp38;
            *dst0++ = D_800FF2DC[i0].unk_02 | D_800FF2E0[i1].unk_02 | D_800FF2E4[i2].unk_02 | 1;
            base = D_800FF2C8[*(u8 *)src1++];
            i0 = base + sp2C;
            i1 = base + sp30 + sp34;
            i2 = base + sp38;
            *dst1++ = D_800FF2DC[i0].unk_02 | D_800FF2E0[i1].unk_02 | D_800FF2E4[i2].unk_02 | 1;
            base = D_800FF2C8[*(u8 *)src1++];
            i0 = base + sp2C;
            i1 = base + sp30 + sp34;
            i2 = base + sp38;
            *dst1++ = D_800FF2DC[i0].unk_02 | D_800FF2E0[i1].unk_02 | D_800FF2E4[i2].unk_02 | 1;
        }
        arg0 = arg0 + (half + half);
        src1 = src1 + (half + half);
        dst0 = dst0 + (half + half);
        dst1 = dst1 + (half + half);
    }
}
