#include "wof.h"

void func_8000CB58(obj_t *obj, frame_t *frame) {
    s32 unused;  /* NOTE: unused in the original */

    if (D_800B3994 >= 318) {
        guTranslate(&frame->translate[obj->index], (f32)obj->x, (f32)obj->y, (f32)obj->z);
        guScale(&frame->scale[obj->index], obj->scale, obj->scale, obj->scale);
        guRotateRPY(&frame->rotate[obj->index], obj->unk_28, obj->unk_2C, obj->unk_30);
        gSPMatrix(D_800B81E8++, &frame->translate[obj->index], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
        gSPMatrix(D_800B81E8++, &frame->scale[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
        gSPMatrix(D_800B81E8++, &frame->rotate[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
        gSPDisplayList(D_800B81E8++, &D_010219C8);
        gSPLightColor(D_800B81E8++, LIGHT_1, 0x111111FF);
        gSPLightColor(D_800B81E8++, LIGHT_2, 0);
        gSPLightColor(D_800B81E8++, LIGHT_3, 0x888888FF);
        gSPLightColor(D_800B81E8++, LIGHT_4, 0x222222FF);
        gSPLightColor(D_800B81E8++, LIGHT_5, 0x222222FF);
        gSPDisplayList(D_800B81E8++, &D_0116C028);
        gSPDisplayList(D_800B81E8++, &D_01166BF8);
    }
    if (D_800B3994 < 318) {
        gSPMatrix(D_800B81E8++, &D_01176D08, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
        guTranslate(&frame->translate[obj->index], (f32)(obj->x + 30), (f32)(obj->y - 50), (f32)(obj->z + 60));
        gSPMatrix(D_800B81E8++, &frame->translate[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
        gSPDisplayList(D_800B81E8++, &D_010219C8);
        gSPLightColor(D_800B81E8++, LIGHT_1, 0);
        gSPLightColor(D_800B81E8++, LIGHT_2, 0);
        gSPLightColor(D_800B81E8++, LIGHT_3, 0);
        gSPLightColor(D_800B81E8++, LIGHT_4, 0x3C3C3CFF);
        gSPLightColor(D_800B81E8++, LIGHT_5, 0x3C3C3CFF);
        gSPDisplayList(D_800B81E8++, &D_011696A0);
        gSPLightColor(D_800B81E8++, LIGHT_1, 0xC8C8C8FF);
    }
}
