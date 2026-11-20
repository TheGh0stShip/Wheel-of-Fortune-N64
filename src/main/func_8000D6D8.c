#include "wof.h"

void func_8000D6D8(s32 arg0, s32 arg1) {
    Gfx *gfx;

    if (D_800B3994 >= 318) {
        return;
    }
    guTranslate(&((frame_t *)arg1)->rotate[((obj_t *)arg0)->index], ((obj_t *)arg0)->x, ((obj_t *)arg0)->y, ((obj_t *)arg0)->z);
    if (((obj_t *)arg0)->unk_3C != 0) {
        gfx = D_800B81E8++;
        gfx->words.w0 = 0x1040040;
        gfx->words.w1 = ((obj_t *)arg0)->unk_3C;
    }
    gfx = D_800B81E8++;
    gfx->words.w0 = 0x1040040;
    gfx->words.w1 = (s32)&((frame_t *)arg1)->rotate[((obj_t *)arg0)->index];
    gfx = D_800B81E8++;
    gfx->words.w0 = 0x6000000;
    gfx->words.w1 = ((obj_t *)arg0)->unk_48;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xBD000000;
    gfx->words.w1 = 0;
    if (((obj_t *)arg0)->unk_3C != 0) {
        gfx = D_800B81E8++;
        gfx->words.w0 = 0xBD000000;
        gfx->words.w1 = 0;
    }
}
