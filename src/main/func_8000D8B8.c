#include "wof.h"

void func_8000D8B8(obj_t *obj, frame_t *frame) {
    s32 i;
    Gfx *gfx;

    if (D_800B3994 < 318) {
        return;
    }
    guTranslate(&frame->translate[obj->index], (f32)obj->x, (f32)obj->y, (f32)obj->z);
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
    gfx = D_800B81E8++;
    gfx->words.w0 = 0x6000000;
    gfx->words.w1 = (s32)D_010FA038;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xBC00000A;
    gfx->words.w1 = 0xC8C8C8FF;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xBC00040A;
    gfx->words.w1 = 0xC8C8C8FF;
    for (i = 0; i < 24; i++) {
        gfx = D_800B81E8++;
        gfx->words.w0 = 0x6000000;
        gfx->words.w1 = D_80057F08[0][i].unk_00;
    }
    gfx = D_800B81E8++;
    gfx->words.w0 = 0x1020040;
    gfx->words.w1 = (s32)&frame->translate[obj->index];
    gfx = D_800B81E8++;
    gfx->words.w0 = 0x6000000;
    gfx->words.w1 = obj->unk_48;
}
