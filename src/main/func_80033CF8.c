#include "wof.h"

void func_80033CF8(obj_t *obj, frame_t *frame) {
    s32 unused;  /* NOTE: unused in the original */

    gDPPipeSync(D_800B81E8++);
    gSPDisplayList(D_800B81E8++, &D_01021970);
    gDPSetCycleType(D_800B81E8++, G_CYC_COPY);
    gDPLoadTextureBlock(D_800B81E8++, obj->unk_44, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0,
                        G_TX_CLAMP, G_TX_CLAMP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);
    gDPPipeSync(D_800B81E8++);
    gSPTextureRectangle(D_800B81E8++, obj->x << 2, obj->y << 2,
                        (obj->x + 31) << 2, (obj->y + 31) << 2,
                        G_TX_RENDERTILE, 0, 0, 4 << 10, 1 << 10);
}
