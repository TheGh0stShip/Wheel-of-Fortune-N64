#include "wof.h"

void func_80014768(s32 arg0, s32 arg1) {
    Gfx *gfx;

    switch (func_80016638()) {
    case 0:
        guTranslate((s32)&((frame_t *)arg1)->translate[((obj_t *)arg0)->index], ((obj_t *)arg0)->x,
                      ((obj_t *)arg0)->y, ((obj_t *)arg0)->z);
        guScale((s32)&((frame_t *)arg1)->scale[((obj_t *)arg0)->index], ((obj_t *)arg0)->scale,
                      ((obj_t *)arg0)->scale, ((obj_t *)arg0)->scale);
        guRotateRPY((s32)&((frame_t *)arg1)->rotate[((obj_t *)arg0)->index], ((obj_t *)arg0)->unk_28,
                      ((obj_t *)arg0)->unk_2C, ((obj_t *)arg0)->unk_30);
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
        gfx->words.w1 = (s32)D_010219C8;
        gfx = D_800B81E8++;
        gfx->words.w0 = 0xBC00000A;
        gfx->words.w1 = 0xC8C8C8FF;
        gfx = D_800B81E8++;
        gfx->words.w0 = 0xBC00040A;
        gfx->words.w1 = 0xC8C8C8FF;
        gfx = D_800B81E8++;
        gfx->words.w0 = 0x6000000;
        gfx->words.w1 = ((obj_t *)arg0)->unk_48;
        func_80005300(1);
    }
}
