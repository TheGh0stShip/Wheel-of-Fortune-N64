#include "wof.h"

void func_800144F0(obj_t *obj, frame_t *frame) {
    Gfx *gfx;

    guTranslate(&frame->translate[obj->index], obj->x, obj->y, obj->z);
    guScale(&frame->scale[obj->index], obj->scale, obj->scale, obj->scale);
    guRotateRPY(&frame->rotate[obj->index], obj->unk_28, obj->unk_2C, obj->unk_30);
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
    gfx->words.w0 = 0x6000000;
    gfx->words.w1 = (s32)D_010219C8;
    func_80005300(1);
    gfx = D_800B81E8++;
    gfx->words.w0 = 0x6000000;
    gfx->words.w1 = obj->unk_48;
    func_80005300(1);
}
