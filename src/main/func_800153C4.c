#include "wof.h"

typedef struct {
    /* 0x0000 */ u8 pad0[0x140];
    /* 0x0140 */ Mtx unk_0140[100];
    /* 0x1A40 */ Mtx unk_1A40[100];
    /* 0x3340 */ Mtx unk_3340[100];
    /* 0x4C40 */ u8 pad4C40[0x40];
    /* 0x4C80 */ Mtx unk_4C80;
} Scene;

extern Gfx *D_800B81E8;

void func_800153C4(s32 arg0, s32 arg1) {
    s32 pad0;
    Gfx *gfx;

    guTranslate(&((Scene *)arg1)->unk_1A40[((obj_t *)arg0)->index], ((obj_t *)arg0)->x, ((obj_t *)arg0)->y, ((obj_t *)arg0)->z);
    guScale(&((Scene *)arg1)->unk_0140[((obj_t *)arg0)->index], ((obj_t *)arg0)->scale, ((obj_t *)arg0)->scale, ((obj_t *)arg0)->scale);
    guRotateRPY(&((Scene *)arg1)->unk_3340[((obj_t *)arg0)->index], ((obj_t *)arg0)->unk_28, ((obj_t *)arg0)->unk_2C, ((obj_t *)arg0)->unk_30);
    gfx = D_800B81E8++;
    gfx->words.w0 = 0x1020040;
    gfx->words.w1 = (s32)&((Scene *)arg1)->unk_1A40[((obj_t *)arg0)->index];
    gfx = D_800B81E8++;
    gfx->words.w0 = 0x1000040;
    gfx->words.w1 = (s32)&((Scene *)arg1)->unk_0140[((obj_t *)arg0)->index];
    gfx = D_800B81E8++;
    gfx->words.w0 = 0x1000040;
    gfx->words.w1 = (s32)&((Scene *)arg1)->unk_3340[((obj_t *)arg0)->index];
    gfx = D_800B81E8++;
    gfx->words.w0 = 0x6000000;
    gfx->words.w1 = (s32)&D_010219C8;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xBC00000A;
    gfx->words.w1 = 0x141414FF;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xBC00040A;
    gfx->words.w1 = 0x141414FF;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xBC00200A;
    gfx->words.w1 = 0xA0A0AFF;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xBC00240A;
    gfx->words.w1 = 0xA0A0AFF;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xBC00400A;
    gfx->words.w1 = 0xA0A0AFF;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xBC00440A;
    gfx->words.w1 = 0xA0A0AFF;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xBC00800A;
    gfx->words.w1 = 0xA0A0AFF;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xBC00840A;
    gfx->words.w1 = 0xA0A0AFF;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0x6000000;
    gfx->words.w1 = ((obj_t *)arg0)->unk_48;
    func_80005300(1);
    func_80005300(2);
    func_80005300(3);
    func_80005300(5);
    gfx = D_800B81E8++;
    gfx->words.w0 = 0x6000000;
    gfx->words.w1 = (s32)&D_010E3748;
}
