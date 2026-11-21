#include "wof.h"

/*
=====================
DrawImageAt

Draws a picture moved by an offset.
=====================
*/
void DrawImageAt(image_t *image, s32 lit, s32 dx, s32 dy) {
    u16 *texture;

    texture = GetImageTexture(image, lit);
    if (texture != 0) {
        gDPLoadTextureBlock(glistp++, texture, G_IM_FMT_RGBA, G_IM_SIZ_16b,
                            image->width, image->height, 0,
                            G_TX_MIRROR | G_TX_WRAP, G_TX_MIRROR | G_TX_WRAP,
                            6, 6, G_TX_NOLOD, G_TX_NOLOD);
        gDPPipeSync(glistp++);
        gSPTextureRectangle(glistp++,
                            (image->x + dx) << 2, (image->y + dy) << 2,
                            (image->x + dx + image->width - 1) << 2,
                            (image->y + dy + image->height - 1) << 2,
                            G_TX_RENDERTILE, 0, 0, 4 << 10, 1 << 10);
        gDPPipeSync(glistp++);
    }
}
