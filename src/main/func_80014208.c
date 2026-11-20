#include "wof.h"

void func_80014208(obj_t *obj, frame_t *frame) {
    s32 i;

    guTranslate(&frame->translate[obj->index], obj->x, obj->y, obj->z);
    guScale(&frame->scale[obj->index], obj->scale, obj->scale, obj->scale);
    guRotateRPY(&frame->rotate[obj->index], obj->unk_28, obj->unk_2C, obj->unk_30);
    gSPMatrix(D_800B81E8++, &frame->translate[obj->index], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(D_800B81E8++, &frame->scale[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
    gSPMatrix(D_800B81E8++, &frame->rotate[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
    gSPDisplayList(D_800B81E8++, obj->unk_48);
    gSPDisplayList(D_800B81E8++, D_01021A70);
    for (i = 0; i < 26; i++) {
        gSPDisplayList(D_800B81E8++, D_80057988[i]);
    }
    func_80005300(1);
}
