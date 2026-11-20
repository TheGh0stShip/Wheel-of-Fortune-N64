#include "wof.h"

void func_800153C4(obj_t *obj, frame_t *frame) {
    s32 unused;  /* NOTE: unused in the original */

    guTranslate(&frame->translate[obj->index], obj->x, obj->y, obj->z);
    guScale(&frame->scale[obj->index], obj->scale, obj->scale, obj->scale);
    guRotateRPY(&frame->rotate[obj->index], obj->unk_28, obj->unk_2C, obj->unk_30);
    gSPMatrix(D_800B81E8++, &frame->translate[obj->index], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(D_800B81E8++, &frame->scale[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
    gSPMatrix(D_800B81E8++, &frame->rotate[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
    gSPDisplayList(D_800B81E8++, &D_010219C8);
    gSPLightColor(D_800B81E8++, LIGHT_1, 0x141414FF);
    gSPLightColor(D_800B81E8++, LIGHT_2, 0xA0A0AFF);
    gSPLightColor(D_800B81E8++, LIGHT_3, 0xA0A0AFF);
    gSPLightColor(D_800B81E8++, LIGHT_5, 0xA0A0AFF);
    gSPDisplayList(D_800B81E8++, obj->unk_48);
    func_80005300(1);
    func_80005300(2);
    func_80005300(3);
    func_80005300(5);
    gSPDisplayList(D_800B81E8++, &D_010E3748);
}
