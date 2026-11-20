#include "wof.h"

void func_800153C4(s32 arg0, s32 arg1) {
    s32 unused;  /* NOTE: unused in the original */

    guTranslate(&((frame_t *)arg1)->translate[((obj_t *)arg0)->index], ((obj_t *)arg0)->x, ((obj_t *)arg0)->y, ((obj_t *)arg0)->z);
    guScale(&((frame_t *)arg1)->scale[((obj_t *)arg0)->index], ((obj_t *)arg0)->scale, ((obj_t *)arg0)->scale, ((obj_t *)arg0)->scale);
    guRotateRPY(&((frame_t *)arg1)->rotate[((obj_t *)arg0)->index], ((obj_t *)arg0)->unk_28, ((obj_t *)arg0)->unk_2C, ((obj_t *)arg0)->unk_30);
    gSPMatrix(D_800B81E8++, &((frame_t *)arg1)->translate[((obj_t *)arg0)->index], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(D_800B81E8++, &((frame_t *)arg1)->scale[((obj_t *)arg0)->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
    gSPMatrix(D_800B81E8++, &((frame_t *)arg1)->rotate[((obj_t *)arg0)->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
    gSPDisplayList(D_800B81E8++, &D_010219C8);
    gSPLightColor(D_800B81E8++, LIGHT_1, 0x141414FF);
    gSPLightColor(D_800B81E8++, LIGHT_2, 0xA0A0AFF);
    gSPLightColor(D_800B81E8++, LIGHT_3, 0xA0A0AFF);
    gSPLightColor(D_800B81E8++, LIGHT_5, 0xA0A0AFF);
    gSPDisplayList(D_800B81E8++, ((obj_t *)arg0)->unk_48);
    func_80005300(1);
    func_80005300(2);
    func_80005300(3);
    func_80005300(5);
    gSPDisplayList(D_800B81E8++, &D_010E3748);
}
