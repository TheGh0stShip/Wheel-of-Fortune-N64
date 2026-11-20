#include "wof.h"

void func_8000D6D8(obj_t *obj, frame_t *frame) {
    if (D_800B3994 >= 318) {
        return;
    }
    guTranslate(&frame->rotate[obj->index], obj->x, obj->y, obj->z);
    if (obj->unk_3C != 0) {
        gSPMatrix(D_800B81E8++, obj->unk_3C, G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
    }
    gSPMatrix(D_800B81E8++, &frame->rotate[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
    gSPDisplayList(D_800B81E8++, obj->unk_48);
    gSPPopMatrix(D_800B81E8++, G_MTX_MODELVIEW);
    if (obj->unk_3C != 0) {
        gSPPopMatrix(D_800B81E8++, G_MTX_MODELVIEW);
    }
}
