#include "wof.h"

void func_800153C4(s32 arg0, s32 arg1) {
    s32 pad0;
    Gfx *gfx;

    guTranslate(&((frame_t *)arg1)->translate[((obj_t *)arg0)->index], ((obj_t *)arg0)->x, ((obj_t *)arg0)->y, ((obj_t *)arg0)->z);
    guScale(&((frame_t *)arg1)->scale[((obj_t *)arg0)->index], ((obj_t *)arg0)->scale, ((obj_t *)arg0)->scale, ((obj_t *)arg0)->scale);
    guRotateRPY(&((frame_t *)arg1)->rotate[((obj_t *)arg0)->index], ((obj_t *)arg0)->unk_28, ((obj_t *)arg0)->unk_2C, ((obj_t *)arg0)->unk_30);
    gfx = D_800B81E8++;
    gfx->words.w0 = 0x1020040;
    gfx->words.w1 = (s32)&((frame_t *)arg1)->translate[((obj_t *)arg0)->index];
    gfx = D_800B81E8++;
    gfx->words.w0 = 0x1000040;
    gfx->words.w1 = (s32)&((frame_t *)arg1)->scale[((obj_t *)arg0)->index];
    gfx = D_800B81E8++;
    gfx->words.w0 = 0x1000040;
    gfx->words.w1 = (s32)&((frame_t *)arg1)->rotate[((obj_t *)arg0)->index];
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
