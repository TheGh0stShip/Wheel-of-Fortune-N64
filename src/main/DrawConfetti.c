#include "wof.h"

void DrawConfetti(obj_t *obj, frame_t *frame) {
    s32 unused;  /* NOTE: unused in the original */

    gDPPipeSync(glistp++);
    gSPDisplayList(glistp++, &D_01021970);
    gDPSetCycleType(glistp++, G_CYC_COPY);
    gDPLoadTextureBlock(glistp++, obj->image, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0,
                        G_TX_CLAMP, G_TX_CLAMP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);
    gDPPipeSync(glistp++);
    gSPTextureRectangle(glistp++, obj->x << 2, obj->y << 2,
                        (obj->x + 31) << 2, (obj->y + 31) << 2,
                        G_TX_RENDERTILE, 0, 0, 4 << 10, 1 << 10);
}
