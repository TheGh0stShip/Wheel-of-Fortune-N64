#include "wof.h"

void func_8000DCA0(obj_t *obj, frame_t *frame) {
    if (D_800B3994 < 318) {
        return;
    }
    obj->unk_2C += (f32)(D_800B96B4 * 2);
    guRotateRPY(&frame->rotate[obj->index], obj->unk_28,
                  obj->unk_2C, obj->unk_30);
    gSPMatrix(D_800B81E8++, &D_01176C88, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(D_800B81E8++, &frame->rotate[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
    gSPDisplayList(D_800B81E8++, D_01166928);
    gSPMatrix(D_800B81E8++, &D_01176CC8, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(D_800B81E8++, &frame->rotate[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
    gSPDisplayList(D_800B81E8++, D_01166598);
    gDPPipeSync(D_800B81E8++);
    gDPSetRenderMode(D_800B81E8++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
}
