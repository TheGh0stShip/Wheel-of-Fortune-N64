#include "wof.h"

void func_8002741C(image_t *image, s32 arg1, s32 arg2, s32 arg3) {
    register s32 reg_s0;
    register s32 reg_s1;
    s32 texture;
    Gfx *gfx;
    Gfx *gfx2;

    texture = func_8002731C(image, arg1);
    if (texture != 0) {
        gfx = D_800B81E8++;
        gfx->words.w0 = 0xFD100000;
        gfx->words.w1 = texture;
        gfx = D_800B81E8++;
        gfx->words.w0 = 0xF5100000;
        gfx->words.w1 = 0x7058160;
        gfx = D_800B81E8++;
        gfx->words.w0 = 0xE6000000;
        gfx->words.w1 = 0;
        gfx = D_800B81E8++;
        gfx->words.w0 = 0xF3000000;
        {
            register Gfx *reg_v0;
            reg_v0 = gfx;
            if (image->width / 4 > 0) {
                reg_s0 = image->width / 4;
                reg_s0 = reg_s0 + 2047;
            } else {
                reg_s0 = 2048;
            }
            reg_s1 = image->width * image->height;
            reg_s1 = reg_s1 - 1;
            if (reg_s1 >= 2048) {
                reg_s1 = 2047;
            }
            reg_s1 = reg_s1 & 4095;
            reg_s1 = reg_s1 << 12;
            reg_s1 = reg_s1 | 0x7000000;
            reg_v0->words.w1 = (image->width / 4 > 0) ? (reg_s1 | ((reg_s0 / (image->width / 4)) & 4095)) : (reg_s1 | (reg_s0 & 4095));
        }
        gfx = D_800B81E8++;
        gfx->words.w0 = 0xE7000000;
        gfx->words.w1 = 0;
        gfx = D_800B81E8++;
        gfx->words.w0 = ((((image->width * 2 + 7) >> 3) & 511) << 9) | 0xF5100000;
        gfx->words.w1 = 0x58160;
        gfx = D_800B81E8++;
        gfx->words.w0 = 0xF2000000;
        gfx->words.w1 = ((((image->width - 1) << 2) & 4095) << 12) | (((image->height - 1) << 2) & 4095);
        gfx = D_800B81E8++;
        gfx->words.w0 = 0xE7000000;
        gfx->words.w1 = 0;
        gfx = D_800B81E8++;
        gfx->words.w0 = ((((image->x + arg2 + image->width - 1) << 2) & 4095) << 12) | 0xE4000000 | (((image->y + arg3 + image->height - 1) << 2) & 4095);
        gfx->words.w1 = ((((image->x + arg2) << 2) & 4095) << 12) | (((image->y + arg3) << 2) & 4095);
        gfx2 = D_800B81E8++;
        gfx2->words.w0 = 0xB4000000;
        gfx2->words.w1 = 0;
        gfx2 = D_800B81E8++;
        gfx2->words.w0 = 0xB3000000;
        gfx2->words.w1 = 0x10000400;
        gfx2 = D_800B81E8++;
        gfx2->words.w0 = 0xE7000000;
        gfx2->words.w1 = 0;
    }
}
