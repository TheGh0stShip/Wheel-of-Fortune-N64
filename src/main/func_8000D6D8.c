#include "wof.h"

void func_8000D6D8(obj_t *obj, frame_t *frame) {
    Gfx *gfx;

    if (D_800B3994 >= 318) {
        return;
    }
    guTranslate(&frame->rotate[obj->index], obj->x, obj->y, obj->z);
    if (obj->unk_3C != 0) {
        gfx = D_800B81E8++;
        gfx->words.w0 = 0x1040040;
        gfx->words.w1 = obj->unk_3C;
    }
    gfx = D_800B81E8++;
    gfx->words.w0 = 0x1040040;
    gfx->words.w1 = (s32)&frame->rotate[obj->index];
    gfx = D_800B81E8++;
    gfx->words.w0 = 0x6000000;
    gfx->words.w1 = obj->unk_48;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xBD000000;
    gfx->words.w1 = 0;
    if (obj->unk_3C != 0) {
        gfx = D_800B81E8++;
        gfx->words.w0 = 0xBD000000;
        gfx->words.w1 = 0;
    }
}
