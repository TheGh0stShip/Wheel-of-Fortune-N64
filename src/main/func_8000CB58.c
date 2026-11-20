#include "wof.h"

typedef struct {
    /* 0x00 */ s32 w0;
    /* 0x04 */ s32 w1;
} Gfx;

typedef struct {
    u8 m[0x40];
} Mtx;

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
    /* 0x18 */ s32 scale;
    /* 0x1C */ u8 unk_1C[0xC];
    /* 0x28 */ s32 unk_28;
    /* 0x2C */ s32 unk_2C;
    /* 0x30 */ s32 unk_30;
    /* 0x34 */ u8 unk_34[0x10];
    /* 0x44 */ s32 unk_44;
    /* 0x48 */ s32 unk_48;
    /* 0x4C */ s32 unk_4C;
} Object;

extern s32 D_010219C8;
extern s32 D_01166BF8;
extern s32 D_011696A0;
extern s32 D_0116C028;
extern s32 D_01176D08;
extern s32 D_800B3994;
extern Gfx *D_800B81E8;
s32 func_8003BFF4(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_8003C09C(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_8003C2F0(s32, f32, f32, f32);

void func_8000CB58(s32 arg0, s32 arg1) {
    s32 pad0;
    Gfx *gfx;

    if (D_800B3994 >= 318) {
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
        gfx->w0 = 0xBC00000A;
        gfx->w1 = 0x111111FF;
        gfx = D_800B81E8++;
        gfx->w0 = 0xBC00040A;
        gfx->w1 = 0x111111FF;
        gfx = D_800B81E8++;
        gfx->w0 = 0xBC00200A;
        gfx->w1 = 0;
        gfx = D_800B81E8++;
        gfx->w0 = 0xBC00240A;
        gfx->w1 = 0;
        gfx = D_800B81E8++;
        gfx->w0 = 0xBC00400A;
        gfx->w1 = 0x888888FF;
        gfx = D_800B81E8++;
        gfx->w0 = 0xBC00440A;
        gfx->w1 = 0x888888FF;
        gfx = D_800B81E8++;
        gfx->w0 = 0xBC00600A;
        gfx->w1 = 0x222222FF;
        gfx = D_800B81E8++;
        gfx->w0 = 0xBC00640A;
        gfx->w1 = 0x222222FF;
        gfx = D_800B81E8++;
        gfx->w0 = 0xBC00800A;
        gfx->w1 = 0x222222FF;
        gfx = D_800B81E8++;
        gfx->w0 = 0xBC00840A;
        gfx->w1 = 0x222222FF;
        gfx = D_800B81E8++;
        gfx->w0 = 0x6000000;
        gfx->w1 = (s32)&D_0116C028;
        gfx = D_800B81E8++;
        gfx->w0 = 0x6000000;
        gfx->w1 = (s32)&D_01166BF8;
    }
    if (D_800B3994 < 318) {
        gfx = D_800B81E8++;
        gfx->w0 = 0x1020040;
        gfx->w1 = (s32)&D_01176D08;
        func_8003C2F0((s32)&((MtxBank *)arg1)->translate[((Object *)arg0)->index], (f32)(((Object *)arg0)->x + 30), (f32)(((Object *)arg0)->y - 50), (f32)(((Object *)arg0)->z + 60));
        gfx = D_800B81E8++;
        gfx->w0 = 0x1000040;
        gfx->w1 = (s32)&((MtxBank *)arg1)->translate[((Object *)arg0)->index];
        gfx = D_800B81E8++;
        gfx->w0 = 0x6000000;
        gfx->w1 = (s32)&D_010219C8;
        gfx = D_800B81E8++;
        gfx->w0 = 0xBC00000A;
        gfx->w1 = 0;
        gfx = D_800B81E8++;
        gfx->w0 = 0xBC00040A;
        gfx->w1 = 0;
        gfx = D_800B81E8++;
        gfx->w0 = 0xBC00200A;
        gfx->w1 = 0;
        gfx = D_800B81E8++;
        gfx->w0 = 0xBC00240A;
        gfx->w1 = 0;
        gfx = D_800B81E8++;
        gfx->w0 = 0xBC00400A;
        gfx->w1 = 0;
        gfx = D_800B81E8++;
        gfx->w0 = 0xBC00440A;
        gfx->w1 = 0;
        gfx = D_800B81E8++;
        gfx->w0 = 0xBC00600A;
        gfx->w1 = 0x3C3C3CFF;
        gfx = D_800B81E8++;
        gfx->w0 = 0xBC00640A;
        gfx->w1 = 0x3C3C3CFF;
        gfx = D_800B81E8++;
        gfx->w0 = 0xBC00800A;
        gfx->w1 = 0x3C3C3CFF;
        gfx = D_800B81E8++;
        gfx->w0 = 0xBC00840A;
        gfx->w1 = 0x3C3C3CFF;
        gfx = D_800B81E8++;
        gfx->w0 = 0x6000000;
        gfx->w1 = (s32)&D_011696A0;
        gfx = D_800B81E8++;
        gfx->w0 = 0xBC00000A;
        gfx->w1 = 0xC8C8C8FF;
        gfx = D_800B81E8++;
        gfx->w0 = 0xBC00040A;
        gfx->w1 = 0xC8C8C8FF;
    }
}
