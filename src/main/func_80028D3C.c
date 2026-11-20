#include "wof.h"

void func_80028D3C(s32 arg0, s32 arg1) {
    s32 unused[4];  /* NOTE: unused in the original; guess: its type, the frame shows at most 16 bytes */

    gDPPipeSync(D_800B81E8++);
    gSPDisplayList(D_800B81E8++, &D_01021970);
    gDPSetCycleType(D_800B81E8++, G_CYC_COPY);
    gDPLoadTextureBlock(D_800B81E8++, ((obj_t *)arg0)->unk_44, G_IM_FMT_RGBA, G_IM_SIZ_16b, 24, 24, 0,
                        G_TX_MIRROR | G_TX_WRAP, G_TX_MIRROR | G_TX_WRAP, 6, 6, G_TX_NOLOD, G_TX_NOLOD);
    gDPPipeSync(D_800B81E8++);
    gSPTextureRectangle(D_800B81E8++, ((obj_t *)arg0)->x << 2, ((obj_t *)arg0)->y << 2,
                        (((obj_t *)arg0)->x + 23) << 2, (((obj_t *)arg0)->y + 23) << 2,
                        G_TX_RENDERTILE, 0, 0, 4 << 10, 1 << 10);
    gDPPipeSync(D_800B81E8++);
}
