#include "wof.h"

void func_80012D40(obj_t *obj, frame_t *frame) {
    switch (func_800166C0()) {
    case 0:
        guTranslate(&frame->translate[obj->index], obj->x, obj->y, obj->z);
        guScale(&frame->scale[obj->index], obj->scale, obj->scale, obj->scale);
        guRotateRPY(&frame->rotate[obj->index], obj->unk_28, obj->unk_2C, obj->unk_30);
        gSPMatrix(D_800B81E8++, &frame->translate[obj->index], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
        gSPMatrix(D_800B81E8++, &frame->scale[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
        gSPMatrix(D_800B81E8++, &frame->rotate[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
        gSPDisplayList(D_800B81E8++, D_010219C8);
        gSPDisplayList(D_800B81E8++, obj->unk_48);
        gSPDisplayList(D_800B81E8++, D_01093D50);
        gDPLoadTextureBlock(D_800B81E8++, D_010A2B88, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0,
                            G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                            5, 5, G_TX_NOLOD, G_TX_NOLOD);
        gSPSetGeometryMode(D_800B81E8++, G_LIGHTING | G_CULL_BACK | G_SHADING_SMOOTH);
        gDPPipeSync(D_800B81E8++);
        func_80012838(D_800B9D08, 12, 1);
        func_80012838(D_800B9E58, 14, 1);
        func_80012838(D_800B9FE0, 14, 1);
        func_80012838(D_800BA168, 12, 1);
        if (D_800BCD54 != 6) {
            gSPDisplayList(D_800B81E8++, D_01021A20);
            func_80012838(D_800B9D08, 12, 0);
            func_80012838(D_800B9E58, 14, 0);
            func_80012838(D_800B9FE0, 14, 0);
            func_80012838(D_800BA168, 12, 0);
        }
        func_80005300(2);
        gDPPipeSync(D_800B81E8++);
    }
}
