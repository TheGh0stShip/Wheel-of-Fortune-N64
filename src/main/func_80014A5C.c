#include "wof.h"

extern Gfx *D_800B81E8;

void func_80014A5C(s32 arg0, s32 arg1) {
    Gfx *gfx;

    guTranslate(&((frame_t *)arg1)->translate[((obj_t *)arg0)->index], ((obj_t *)arg0)->x, ((obj_t *)arg0)->y, ((obj_t *)arg0)->z);
    guScale(&((frame_t *)arg1)->scale[((obj_t *)arg0)->index], ((obj_t *)arg0)->scale, ((obj_t *)arg0)->scale, ((obj_t *)arg0)->scale);
    guRotateRPY(&((frame_t *)arg1)->rotate[((obj_t *)arg0)->index], ((obj_t *)arg0)->unk_28, ((obj_t *)arg0)->unk_2C, ((obj_t *)arg0)->unk_30);
    gfx = D_800B81E8++;
    gfx->words.w0 = 0x1020040;
    gfx->words.w1 = (u32)&((frame_t *)arg1)->translate[((obj_t *)arg0)->index];
    gfx = D_800B81E8++;
    gfx->words.w0 = 0x1000040;
    gfx->words.w1 = (u32)&((frame_t *)arg1)->scale[((obj_t *)arg0)->index];
    gfx = D_800B81E8++;
    gfx->words.w0 = 0x1000040;
    gfx->words.w1 = (u32)&((frame_t *)arg1)->rotate[((obj_t *)arg0)->index];
    gfx = D_800B81E8++;
    gfx->words.w0 = 0x6000000;
    gfx->words.w1 = (u32)&D_010219C8;
    func_80005300(1);
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xBC00200A;
    gfx->words.w1 = 0x55555555;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xBC00240A;
    gfx->words.w1 = 0x55555555;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xBC00400A;
    gfx->words.w1 = 0x55555555;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xBC00440A;
    gfx->words.w1 = 0x55555555;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xBC00600A;
    gfx->words.w1 = 0x55555555;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xBC00640A;
    gfx->words.w1 = 0x55555555;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xBC00800A;
    gfx->words.w1 = 0x55555555;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xBC00840A;
    gfx->words.w1 = 0x55555555;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0x6000000;
    gfx->words.w1 = ((obj_t *)arg0)->unk_48;
    func_80005300(2);
    func_80005300(3);
    func_80005300(4);
    func_80005300(5);
    if (D_80057F34[D_800B81E0] != 0) {
        gfx = D_800B81E8++;
        gfx->words.w0 = 0x6000000;
        gfx->words.w1 = D_80057F34[D_800B81E0];
    }
    func_80005300(1);
}
