#include "wof.h"

void func_8000D400(s32 arg0, s32 arg1) {
    Gfx *gfx;

    if (D_800B3994 >= 318) {
        return;
    }
    guTranslate(&((frame_t *)arg1)->translate[((obj_t *)arg0)->index], ((obj_t *)arg0)->x, ((obj_t *)arg0)->y, ((obj_t *)arg0)->z);
    guScale(&((frame_t *)arg1)->scale[((obj_t *)arg0)->index], ((obj_t *)arg0)->scale, ((obj_t *)arg0)->scale, ((obj_t *)arg0)->scale);
    guRotateRPY(&((frame_t *)arg1)->rotate[((obj_t *)arg0)->index], ((obj_t *)arg0)->unk_28, ((obj_t *)arg0)->unk_2C, ((obj_t *)arg0)->unk_30);
    guRotateRPY(&((frame_t *)arg1)->unk_04C80, 0, D_800B61AC, 0);
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
    gfx->words.w0 = 0x1000040;
    gfx->words.w1 = (s32)&((frame_t *)arg1)->unk_04C80;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0x6000000;
    gfx->words.w1 = (s32)&D_010219C8;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0x6000000;
    gfx->words.w1 = ((obj_t *)arg0)->unk_48;
}
