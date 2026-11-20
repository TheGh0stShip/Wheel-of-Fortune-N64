#include "wof.h"

void func_8000D400(obj_t *obj, frame_t *frame) {
    Gfx *gfx;

    if (D_800B3994 >= 318) {
        return;
    }
    guTranslate(&frame->translate[obj->index], obj->x, obj->y, obj->z);
    guScale(&frame->scale[obj->index], obj->scale, obj->scale, obj->scale);
    guRotateRPY(&frame->rotate[obj->index], obj->unk_28, obj->unk_2C, obj->unk_30);
    guRotateRPY(&frame->unk_04C80, 0, D_800B61AC, 0);
    gfx = D_800B81E8++;
    gfx->words.w0 = 0x1020040;
    gfx->words.w1 = (s32)&frame->translate[obj->index];
    gfx = D_800B81E8++;
    gfx->words.w0 = 0x1000040;
    gfx->words.w1 = (s32)&frame->scale[obj->index];
    gfx = D_800B81E8++;
    gfx->words.w0 = 0x1000040;
    gfx->words.w1 = (s32)&frame->rotate[obj->index];
    gfx = D_800B81E8++;
    gfx->words.w0 = 0x1000040;
    gfx->words.w1 = (s32)&frame->unk_04C80;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0x6000000;
    gfx->words.w1 = (s32)D_010219C8;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0x6000000;
    gfx->words.w1 = obj->unk_48;
}
