#include "wof.h"

void func_80013748(obj_t *obj, frame_t *frame) {
    s32 i;
    s32 j;
    s32 color;

    switch (func_80016638()) {
    case 0:
        guTranslate(&frame->translate[obj->index], obj->x, obj->y, obj->z);
        guScale(&frame->scale[obj->index], obj->scale, obj->scale, obj->scale);
        guRotateRPY(&frame->rotate[obj->index], obj->unk_28, obj->unk_2C, obj->unk_30);
        gSPMatrix(D_800B81E8++, &frame->translate[obj->index], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
        gSPMatrix(D_800B81E8++, &frame->scale[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
        gSPMatrix(D_800B81E8++, &frame->rotate[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
        gSPDisplayList(D_800B81E8++, D_01021AC8);
        for (i = 0; i < 3; i++) {
            color = func_80013440(&D_80057BB0[i]);
            gSPLightColor(D_800B81E8++, LIGHT_1, color);
            gSPLightColor(D_800B81E8++, LIGHT_3, color);
            gSPLightColor(D_800B81E8++, LIGHT_4, color);
            gSPLightColor(D_800B81E8++, LIGHT_5, color);
            gSPDisplayList(D_800B81E8++, D_80057BB0[i].unk_00);
        }
        func_80005300(1);
        func_80005300(3);
        func_80005300(4);
        func_80005300(5);
        gDPPipeSync(D_800B81E8++);
        gSPDisplayList(D_800B81E8++, D_010219C8);
        gSPSetGeometryMode(D_800B81E8++, G_LIGHTING | G_CULL_BACK | G_SHADING_SMOOTH);
        gDPLoadTextureBlock(D_800B81E8++, D_010367A8, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0,
                            G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                            5, 5, G_TX_NOLOD, G_TX_NOLOD);
        gDPPipeSync(D_800B81E8++);
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 8; j++) {
                if (D_800BEEA8[i][j] == (s32)D_010367A8) {
                    gSPDisplayList(D_800B81E8++, D_80057B50[i][j]);
                }
            }
        }
        i = 0;
        while (i < 3) {
            for (j = 0; j < 8; j++) {
                if (D_800BEEA8[i][j] != (s32)D_010367A8) {
                    gDPLoadTextureBlock(D_800B81E8++, D_800BEEA8[i][j], G_IM_FMT_RGBA, G_IM_SIZ_16b,
                                        32, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                                        G_TX_NOMIRROR | G_TX_CLAMP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);
                    gDPPipeSync(D_800B81E8++);
                    gSPDisplayList(D_800B81E8++, D_80057B50[i][j]);
                }
            }
            i++;
        }
        gSPDisplayList(D_800B81E8++, D_010308D0);
    }
}
