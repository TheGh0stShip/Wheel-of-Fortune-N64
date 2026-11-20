#include "wof.h"

void func_80014208(s32 arg0, s32 arg1) {
    s32 i;
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
    gfx->words.w1 = ((obj_t *)arg0)->unk_48;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0x6000000;
    gfx->words.w1 = (s32)&D_01021A70;
    for (i = 0; i < 26; i++) {
        gfx = D_800B81E8++;
        gfx->words.w0 = 0x6000000;
        gfx->words.w1 = D_80057988[i];
    }
    func_80005300(1);
}
