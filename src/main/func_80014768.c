#include "wof.h"

void func_80014768(obj_t *obj, frame_t *frame) {
    switch (func_80016638()) {
    case 0:
        guTranslate(&frame->translate[obj->index], obj->x,
                      obj->y, obj->z);
        guScale(&frame->scale[obj->index], obj->scale,
                      obj->scale, obj->scale);
        guRotateRPY(&frame->rotate[obj->index], obj->unk_28,
                      obj->unk_2C, obj->unk_30);
        gSPMatrix(D_800B81E8++, &frame->translate[obj->index], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
        gSPMatrix(D_800B81E8++, &frame->scale[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
        gSPMatrix(D_800B81E8++, &frame->rotate[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
        gSPDisplayList(D_800B81E8++, D_010219C8);
        gSPLightColor(D_800B81E8++, LIGHT_1, 0xC8C8C8FF);
        gSPDisplayList(D_800B81E8++, obj->unk_48);
        func_80005300(1);
    }
}
