#include "wof.h"

void func_80014F38(obj_t *obj, frame_t *frame) {
    s32 i;
    Gfx *gfx;

    switch (func_80016638()) {
    case 0:
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
        gfx = D_800B81E8++;
        gfx->words.w0 = 0x6000000;
        gfx->words.w1 = (u32)D_010FA038;
        gfx = D_800B81E8++;
        gfx->words.w0 = 0xBC00000A;
        gfx->words.w1 = 0xC8C8C8FF;
        gfx = D_800B81E8++;
        gfx->words.w0 = 0xBC00040A;
        gfx->words.w1 = 0xC8C8C8FF;
        i = 0;
        while (i < 24) {
            if (D_800B39B8[i].unk_1C != 0 && D_80057F08[D_800B619C][i].unk_04 != 0) {
                gfx = D_800B81E8++;
                gfx->words.w0 = 0x6000000;
                gfx->words.w1 = D_80057F08[D_800B619C][i].unk_04;
            } else {
                gfx = D_800B81E8++;
                gfx->words.w0 = 0x6000000;
                gfx->words.w1 = D_80057F08[D_800B619C][i].unk_00;
            }
            i++;
        }
        func_80005300(1);
        gfx = D_800B81E8++;
        gfx->words.w0 = 0x6000000;
        gfx->words.w1 = obj->unk_48;
        func_80005300(1);
    }
}
