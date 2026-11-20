#include "wof.h"

void func_80016C78(s32 arg0, s32 arg1) {
    s32 frame;
    u16 perspNorm;
    f32 eye[4][4];
    f32 scale[4][4];
    f32 rot[4][4];
    f32 up[4][4];

    guPerspective(&((frame_t *)arg1)->projection, &perspNorm, 33.0f, 4.0f / 3.0f, 200.0f, 5000.0f, ((obj_t *)arg0)->scale);
    gSPPerspNormalize(D_800B81E8++, perspNorm);
    if (D_800BCD54 == 1) {
        frame = D_800B3994;
        if (frame < 0) {
            frame = 0;
        }
        if (D_800B6198 - 1 < frame) {
            frame = D_800B6198 - 1;
        }
        guLookAt(&((frame_t *)arg1)->viewing, D_8005EB48[frame].eyeX, D_8005EB48[frame].eyeY, D_8005EB48[frame].eyeZ, D_8005EB48[frame].atX, D_8005EB48[frame].atY, D_8005EB48[frame].atZ, D_8005EB48[frame].upX, D_8005EB48[frame].upY, D_8005EB48[frame].upZ);
    } else if (D_800BA5D8 != 0) {
        if (D_800B6BE8 + D_800B6BEC + D_800B6BF0 == 0.0f) {
            guLookAt(&((frame_t *)arg1)->viewing, D_800BA5D8->eyeX, D_800BA5D8->eyeY, D_800BA5D8->eyeZ, D_800BA5D8->atX, D_800BA5D8->atY, D_800BA5D8->atZ, 0.0f, 1.0f, 0.0f);
        } else {
            guLookAt(&((frame_t *)arg1)->viewing, D_800BA5D8->eyeX, D_800BA5D8->eyeY, D_800BA5D8->eyeZ, D_800BA5D8->atX, D_800BA5D8->atY, D_800BA5D8->atZ, D_800B6BE8, D_800B6BEC, D_800B6BF0);
        }
    } else {
        guTranslateF(eye, 0, 0, -1000.0f);
        guScaleF(scale, ((obj_t *)arg0)->scale, ((obj_t *)arg0)->scale, ((obj_t *)arg0)->scale);
        guRotateRPYF(rot, ((obj_t *)arg0)->unk_28, ((obj_t *)arg0)->unk_2C, ((obj_t *)arg0)->unk_30);
        guMtxCatF(eye, scale, eye);
        guMtxCatF(eye, rot, eye);
        guTranslateF(up, 0, 1.0f, 0);
        guScaleF(scale, ((obj_t *)arg0)->scale, ((obj_t *)arg0)->scale, ((obj_t *)arg0)->scale);
        guRotateRPYF(rot, ((obj_t *)arg0)->unk_28, ((obj_t *)arg0)->unk_2C, ((obj_t *)arg0)->unk_30);
        guMtxCatF(up, scale, up);
        guMtxCatF(up, rot, up);
        guLookAt(&((frame_t *)arg1)->viewing, ((obj_t *)arg0)->x, ((obj_t *)arg0)->y, ((obj_t *)arg0)->z, eye[3][0] + ((obj_t *)arg0)->x, eye[3][1] + ((obj_t *)arg0)->y, eye[3][2] + ((obj_t *)arg0)->z, up[3][0], up[3][1], up[3][2]);
    }
    gSPMatrix(D_800B81E8++, &((frame_t *)arg1)->projection, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(D_800B81E8++, &((frame_t *)arg1)->viewing, G_MTX_PROJECTION | G_MTX_MUL | G_MTX_NOPUSH);
    gSPSetLights6(D_800B81E8++, D_8004B7B8);
}
