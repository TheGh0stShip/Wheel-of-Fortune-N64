#include "wof.h"

typedef struct {
    /* 0x0000 */ u8 pad0[0x140];
    /* 0x0140 */ Mtx unk_0140[100];
    /* 0x1A40 */ Mtx unk_1A40[100];
    /* 0x3340 */ Mtx unk_3340[100];
    /* 0x4C40 */ u8 pad4C40[0x40];
    /* 0x4C80 */ Mtx unk_4C80;
} Scene;

typedef struct {
    /* 0x00 */ s32 index;
    /* 0x04 */ u8 pad4[0xC];
    /* 0x10 */ s16 x;
    /* 0x12 */ s16 y;
    /* 0x14 */ s16 z;
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ u8 pad1C[0xC];
    /* 0x28 */ f32 unk_28;
    /* 0x2C */ f32 unk_2C;
    /* 0x30 */ f32 unk_30;
    /* 0x34 */ u8 pad34[0x8];
    /* 0x3C */ s32 unk_3C;
    /* 0x40 */ u8 pad40[0x8];
    /* 0x48 */ s32 unk_48;
} Model;

extern Gfx *D_800B81E8;

void func_800153C4(s32 arg0, s32 arg1) {
    s32 pad0;
    Gfx *gfx;

    func_8003C2F0(&((Scene *)arg1)->unk_1A40[((Model *)arg0)->index], ((Model *)arg0)->x, ((Model *)arg0)->y, ((Model *)arg0)->z);
    func_8003C09C(&((Scene *)arg1)->unk_0140[((Model *)arg0)->index], ((Model *)arg0)->unk_18, ((Model *)arg0)->unk_18, ((Model *)arg0)->unk_18);
    func_8003BFF4(&((Scene *)arg1)->unk_3340[((Model *)arg0)->index], ((Model *)arg0)->unk_28, ((Model *)arg0)->unk_2C, ((Model *)arg0)->unk_30);
    gfx = D_800B81E8++;
    gfx->w0 = 0x1020040;
    gfx->w1 = (s32)&((Scene *)arg1)->unk_1A40[((Model *)arg0)->index];
    gfx = D_800B81E8++;
    gfx->w0 = 0x1000040;
    gfx->w1 = (s32)&((Scene *)arg1)->unk_0140[((Model *)arg0)->index];
    gfx = D_800B81E8++;
    gfx->w0 = 0x1000040;
    gfx->w1 = (s32)&((Scene *)arg1)->unk_3340[((Model *)arg0)->index];
    gfx = D_800B81E8++;
    gfx->w0 = 0x6000000;
    gfx->w1 = (s32)&D_010219C8;
    gfx = D_800B81E8++;
    gfx->w0 = 0xBC00000A;
    gfx->w1 = 0x141414FF;
    gfx = D_800B81E8++;
    gfx->w0 = 0xBC00040A;
    gfx->w1 = 0x141414FF;
    gfx = D_800B81E8++;
    gfx->w0 = 0xBC00200A;
    gfx->w1 = 0xA0A0AFF;
    gfx = D_800B81E8++;
    gfx->w0 = 0xBC00240A;
    gfx->w1 = 0xA0A0AFF;
    gfx = D_800B81E8++;
    gfx->w0 = 0xBC00400A;
    gfx->w1 = 0xA0A0AFF;
    gfx = D_800B81E8++;
    gfx->w0 = 0xBC00440A;
    gfx->w1 = 0xA0A0AFF;
    gfx = D_800B81E8++;
    gfx->w0 = 0xBC00800A;
    gfx->w1 = 0xA0A0AFF;
    gfx = D_800B81E8++;
    gfx->w0 = 0xBC00840A;
    gfx->w1 = 0xA0A0AFF;
    gfx = D_800B81E8++;
    gfx->w0 = 0x6000000;
    gfx->w1 = ((Model *)arg0)->unk_48;
    func_80005300(1);
    func_80005300(2);
    func_80005300(3);
    func_80005300(5);
    gfx = D_800B81E8++;
    gfx->w0 = 0x6000000;
    gfx->w1 = (s32)&D_010E3748;
}
