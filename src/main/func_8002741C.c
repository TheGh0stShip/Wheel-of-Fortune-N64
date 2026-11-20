#include "wof.h"

void func_8002741C(image_t *image, s32 arg1, s32 arg2, s32 arg3) {
    s32 texture;

    texture = func_8002731C(image, arg1);
    if (texture != 0) {
        gDPLoadTextureBlock(D_800B81E8++, texture, G_IM_FMT_RGBA, G_IM_SIZ_16b,
                            image->width, image->height, 0,
                            G_TX_MIRROR | G_TX_WRAP, G_TX_MIRROR | G_TX_WRAP,
                            6, 6, G_TX_NOLOD, G_TX_NOLOD);
        gDPPipeSync(D_800B81E8++);
        gSPTextureRectangle(D_800B81E8++,
                            (image->x + arg2) << 2, (image->y + arg3) << 2,
                            (image->x + arg2 + image->width - 1) << 2,
                            (image->y + arg3 + image->height - 1) << 2,
                            G_TX_RENDERTILE, 0, 0, 4 << 10, 1 << 10);
        gDPPipeSync(D_800B81E8++);
    }
}
