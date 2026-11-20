#include "wof.h"

void func_8000DF2C(s32 arg0, s32 arg1) {
    s32 unused[2];  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */
    s32 row;
    s32 col;

    gSPDisplayList(D_800B81E8++, &D_01021970);
    gDPSetCycleType(D_800B81E8++, G_CYC_COPY);
    gDPSetTextureLUT(D_800B81E8++, G_TT_RGBA16);
    gDPLoadTLUT_pal16(D_800B81E8++, 0, &D_01146E68);
    gDPPipeSync(D_800B81E8++);
    for (row = 0; row < 2; row++) {
        for (col = 0; col < 3; col++) {
            gDPLoadTextureBlock_4b(D_800B81E8++, D_80057970[row][col], G_IM_FMT_CI, 64, 64, 0,
                                   G_TX_MIRROR | G_TX_WRAP, G_TX_MIRROR | G_TX_WRAP,
                                   G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            gDPPipeSync(D_800B81E8++);
            gSPTextureRectangle(D_800B81E8++,
                                (((obj_t *)arg0)->x + col * 64) << 2, (((obj_t *)arg0)->y + row * 64) << 2,
                                (((obj_t *)arg0)->x + col * 64 + 63) << 2, (((obj_t *)arg0)->y + row * 64 + 63) << 2,
                                G_TX_RENDERTILE, 0, 0, 4 << 10, 1 << 10);
            gDPPipeSync(D_800B81E8++);
        }
    }
}
