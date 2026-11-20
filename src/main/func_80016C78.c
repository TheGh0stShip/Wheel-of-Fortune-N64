#include "wof.h"

void func_80016C78(obj_t *obj, frame_t *frame) {
    s32 step;
    u16 perspNorm;
    f32 eye[4][4];
    f32 scale[4][4];
    f32 rot[4][4];
    f32 up[4][4];

    guPerspective(&frame->projection, &perspNorm, 33.0f, 4.0f / 3.0f, 200.0f, 5000.0f, obj->scale);
    gSPPerspNormalize(D_800B81E8++, perspNorm);
    if (D_800BCD54 == 1) {
        step = D_800B3994;
        if (step < 0) {
            step = 0;
        }
        if (D_800B6198 - 1 < step) {
            step = D_800B6198 - 1;
        }
        guLookAt(&frame->viewing, D_8005EB48[step].eyeX, D_8005EB48[step].eyeY, D_8005EB48[step].eyeZ, D_8005EB48[step].atX, D_8005EB48[step].atY, D_8005EB48[step].atZ, D_8005EB48[step].upX, D_8005EB48[step].upY, D_8005EB48[step].upZ);
    } else if (D_800BA5D8 != 0) {
        if (D_800B6BE8 + D_800B6BEC + D_800B6BF0 == 0.0f) {
            guLookAt(&frame->viewing, D_800BA5D8->eyeX, D_800BA5D8->eyeY, D_800BA5D8->eyeZ, D_800BA5D8->atX, D_800BA5D8->atY, D_800BA5D8->atZ, 0.0f, 1.0f, 0.0f);
        } else {
            guLookAt(&frame->viewing, D_800BA5D8->eyeX, D_800BA5D8->eyeY, D_800BA5D8->eyeZ, D_800BA5D8->atX, D_800BA5D8->atY, D_800BA5D8->atZ, D_800B6BE8, D_800B6BEC, D_800B6BF0);
        }
    } else {
        guTranslateF(eye, 0, 0, -1000.0f);
        guScaleF(scale, obj->scale, obj->scale, obj->scale);
        guRotateRPYF(rot, obj->unk_28, obj->unk_2C, obj->unk_30);
        guMtxCatF(eye, scale, eye);
        guMtxCatF(eye, rot, eye);
        guTranslateF(up, 0, 1.0f, 0);
        guScaleF(scale, obj->scale, obj->scale, obj->scale);
        guRotateRPYF(rot, obj->unk_28, obj->unk_2C, obj->unk_30);
        guMtxCatF(up, scale, up);
        guMtxCatF(up, rot, up);
        guLookAt(&frame->viewing, obj->x, obj->y, obj->z, eye[3][0] + obj->x, eye[3][1] + obj->y, eye[3][2] + obj->z, up[3][0], up[3][1], up[3][2]);
    }
    gSPMatrix(D_800B81E8++, &frame->projection, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(D_800B81E8++, &frame->viewing, G_MTX_PROJECTION | G_MTX_MUL | G_MTX_NOPUSH);
    gSPSetLights6(D_800B81E8++, D_8004B7B8);
}
