#include "wof.h"

void func_8000CB58(s32 arg0, s32 arg1) {
    s32 unused;  /* NOTE: unused in the original */

    if (D_800B3994 >= 318) {
        guTranslate((s32)&((frame_t *)arg1)->translate[((obj_t *)arg0)->index], (f32)((obj_t *)arg0)->x, (f32)((obj_t *)arg0)->y, (f32)((obj_t *)arg0)->z);
        guScale((s32)&((frame_t *)arg1)->scale[((obj_t *)arg0)->index], ((obj_t *)arg0)->scale, ((obj_t *)arg0)->scale, ((obj_t *)arg0)->scale);
        guRotateRPY((s32)&((frame_t *)arg1)->rotate[((obj_t *)arg0)->index], ((obj_t *)arg0)->unk_28, ((obj_t *)arg0)->unk_2C, ((obj_t *)arg0)->unk_30);
        gSPMatrix(D_800B81E8++, &((frame_t *)arg1)->translate[((obj_t *)arg0)->index], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
        gSPMatrix(D_800B81E8++, &((frame_t *)arg1)->scale[((obj_t *)arg0)->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
        gSPMatrix(D_800B81E8++, &((frame_t *)arg1)->rotate[((obj_t *)arg0)->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
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
        guTranslate((s32)&((frame_t *)arg1)->translate[((obj_t *)arg0)->index], (f32)(((obj_t *)arg0)->x + 30), (f32)(((obj_t *)arg0)->y - 50), (f32)(((obj_t *)arg0)->z + 60));
        gSPMatrix(D_800B81E8++, &((frame_t *)arg1)->translate[((obj_t *)arg0)->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
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
