#include "wof.h"

void func_80014A5C(obj_t *obj, frame_t *frame) {
    guTranslate(&frame->translate[obj->index], obj->x, obj->y, obj->z);
    guScale(&frame->scale[obj->index], obj->scale, obj->scale, obj->scale);
    guRotateRPY(&frame->rotate[obj->index], obj->unk_28, obj->unk_2C, obj->unk_30);
    gSPMatrix(D_800B81E8++, &frame->translate[obj->index], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(D_800B81E8++, &frame->scale[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
    gSPMatrix(D_800B81E8++, &frame->rotate[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
    gSPDisplayList(D_800B81E8++, D_010219C8);
    func_80005300(1);
    gSPLightColor(D_800B81E8++, LIGHT_2, 0x55555555);
    gSPLightColor(D_800B81E8++, LIGHT_3, 0x55555555);
    gSPLightColor(D_800B81E8++, LIGHT_4, 0x55555555);
    gSPLightColor(D_800B81E8++, LIGHT_5, 0x55555555);
    gSPDisplayList(D_800B81E8++, obj->unk_48);
    func_80005300(2);
    func_80005300(3);
    func_80005300(4);
    func_80005300(5);
    if (D_80057F34[D_800B81E0] != 0) {
        gSPDisplayList(D_800B81E8++, D_80057F34[D_800B81E0]);
    }
    func_80005300(1);
}
