#include "wof.h"

typedef struct {
    /* 0x0000 */ u8 unk_0000[0x140];
    /* 0x0140 */ Mtx scale[100];
    /* 0x1A40 */ Mtx translate[100];
    /* 0x3340 */ Mtx rotate[1];
} MtxBank;

typedef struct {
    /* 0x00 */ s32 index;
    /* 0x04 */ u8 unk_04[0xC];
    /* 0x10 */ s16 x;
    /* 0x12 */ s16 y;
    /* 0x14 */ s16 z;
    /* 0x16 */ u8 unk_16[0x2];
    /* 0x18 */ f32 scale;
    /* 0x1C */ u8 unk_1C[0xC];
    /* 0x28 */ f32 unk_28;
    /* 0x2C */ f32 unk_2C;
    /* 0x30 */ f32 unk_30;
    /* 0x34 */ u8 unk_34[0x10];
    /* 0x44 */ s32 unk_44;
    /* 0x48 */ s32 unk_48;
    /* 0x4C */ s32 unk_4C;
} Object;

extern Gfx *D_800B81E8;

void func_80030490(s32 arg0, s32 arg1) {
    Gfx *gfx;

    if (((Object *)arg0)->unk_44 == 0) {
        return;
    }
    func_8003C2F0((s32)&((MtxBank *)arg1)->translate[((Object *)arg0)->index], (f32)((Object *)arg0)->x, (f32)((Object *)arg0)->y, (f32)((Object *)arg0)->z);
    func_8003C09C((s32)&((MtxBank *)arg1)->scale[((Object *)arg0)->index], ((Object *)arg0)->scale, ((Object *)arg0)->scale, ((Object *)arg0)->scale);
    func_8003BFF4((s32)&((MtxBank *)arg1)->rotate[((Object *)arg0)->index], ((Object *)arg0)->unk_28, ((Object *)arg0)->unk_2C, ((Object *)arg0)->unk_30);
    gfx = D_800B81E8++;
    gfx->w0 = 0x1020040;
    gfx->w1 = (s32)&((MtxBank *)arg1)->translate[((Object *)arg0)->index];
    gfx = D_800B81E8++;
    gfx->w0 = 0x1000040;
    gfx->w1 = (s32)&((MtxBank *)arg1)->scale[((Object *)arg0)->index];
    gfx = D_800B81E8++;
    gfx->w0 = 0x1000040;
    gfx->w1 = (s32)&((MtxBank *)arg1)->rotate[((Object *)arg0)->index];
    gfx = D_800B81E8++;
    gfx->w0 = 0x6000000;
    gfx->w1 = (s32)&D_010219C8;
    gfx = D_800B81E8++;
    gfx->w0 = 0xBB000001;
    gfx->w1 = -1;
    gfx = D_800B81E8++;
    gfx->w0 = 0xE7000000;
    gfx->w1 = 0;
    gfx = D_800B81E8++;
    gfx->w0 = 0xB900031D;
    gfx->w1 = 0x553078;
    gfx = D_800B81E8++;
    gfx->w0 = 0xFC127E24;
    gfx->w1 = -3079;
    gfx = D_800B81E8++;
    gfx->w0 = 0xFD100000;
    gfx->w1 = ((Object *)arg0)->unk_44;
    gfx = D_800B81E8++;
    gfx->w0 = 0xF5100000;
    gfx->w1 = 0x7098250;
    gfx = D_800B81E8++;
    gfx->w0 = 0xE6000000;
    gfx->w1 = 0;
    gfx = D_800B81E8++;
    gfx->w0 = 0xF3000000;
    gfx->w1 = 0x77FF100;
    gfx = D_800B81E8++;
    gfx->w0 = 0xE7000000;
    gfx->w1 = 0;
    gfx = D_800B81E8++;
    gfx->w0 = 0xF5101000;
    gfx->w1 = 0x98250;
    gfx = D_800B81E8++;
    gfx->w0 = 0xF2000000;
    gfx->w1 = 0x7C0FC;
    gfx = D_800B81E8++;
    gfx->w0 = 0xE7000000;
    gfx->w1 = 0;
    gfx = D_800B81E8++;
    gfx->w0 = 0x6000000;
    gfx->w1 = ((Object *)arg0)->unk_48;
    gfx = D_800B81E8++;
    gfx->w0 = 0xFD100000;
    gfx->w1 = ((Object *)arg0)->unk_44 + 0x1000;
    gfx = D_800B81E8++;
    gfx->w0 = 0xF5100000;
    gfx->w1 = 0x7098250;
    gfx = D_800B81E8++;
    gfx->w0 = 0xE6000000;
    gfx->w1 = 0;
    gfx = D_800B81E8++;
    gfx->w0 = 0xF3000000;
    gfx->w1 = 0x77FF100;
    gfx = D_800B81E8++;
    gfx->w0 = 0xE7000000;
    gfx->w1 = 0;
    gfx = D_800B81E8++;
    gfx->w0 = 0xF5101000;
    gfx->w1 = 0x98250;
    gfx = D_800B81E8++;
    gfx->w0 = 0xF2000000;
    gfx->w1 = 0x7C0FC;
    gfx = D_800B81E8++;
    gfx->w0 = 0x6000000;
    gfx->w1 = ((Object *)arg0)->unk_4C;
    gfx = D_800B81E8++;
    gfx->w0 = 0xE7000000;
    gfx->w1 = 0;
    gfx = D_800B81E8++;
    gfx->w0 = 0xB900031D;
    gfx->w1 = 0x552078;
}
