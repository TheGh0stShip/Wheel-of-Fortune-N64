#include "wof.h"

void func_80014A5C(obj_t *obj, frame_t *frame) {
    Gfx *gfx;

    guTranslate(&frame->translate[obj->index], obj->x, obj->y, obj->z);
    guScale(&frame->scale[obj->index], obj->scale, obj->scale, obj->scale);
    guRotateRPY(&frame->rotate[obj->index], obj->unk_28, obj->unk_2C, obj->unk_30);
    gfx = D_800B81E8++;
    gfx->words.w0 = 0x1020040;
    gfx->words.w1 = (u32)&frame->translate[obj->index];
    gfx = D_800B81E8++;
    gfx->words.w0 = 0x1000040;
    gfx->words.w1 = (u32)&frame->scale[obj->index];
    gfx = D_800B81E8++;
    gfx->words.w0 = 0x1000040;
    gfx->words.w1 = (u32)&frame->rotate[obj->index];
    gfx = D_800B81E8++;
    gfx->words.w0 = 0x6000000;
    gfx->words.w1 = (u32)D_010219C8;
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
    gfx->words.w1 = obj->unk_48;
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
