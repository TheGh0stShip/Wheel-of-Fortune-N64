// wof_image.c -- the obj of a picture on the screen, which of its textures to draw, and drawing it
//
// MakeScreenObj and GetImageTexture each end off an 8-byte boundary with the next function right
// after, which happens only inside an object. The object starts after the 4-byte gap that ends
// InitOptions, where the RCS run at 0x80001678 opens its read-only data; whether it runs on after
// DrawImageAt the text does not say.

#include "wof.h"

// The #ident line of the system header this object included: the original assembler put the string
// into the read-only data, which it opens. The header is not in this tree, so its line stands here.
#ident "$Revision: 1.17 $"

/*
=====================
MakeScreenObj

MakeObj for a picture on the screen: placed in front of the camera.
=====================
*/
obj_t *MakeScreenObj(proc_t *proc, Gfx *dl, objDraw_t draw, s32 cls) {
    obj_t *obj;
    s32 owner;

    owner = 0;
    if (proc != 0) {
        owner = proc->id;
    }
    obj = CreatObj(owner, draw, cls);
    if (obj == 0) {
        return obj;
    }
    if (proc != 0) {
        proc->data->obj = obj;
    }
    obj->scale = 1.0f;
    obj->x = -160;
    obj->y = -80;
    obj->z = -450;
    obj->roll = 0;
    obj->pitch = 0;
    obj->heading = 0;
    obj->dl = dl;
    return obj;
}

/*
=====================
GetImageTexture

Which of a picture's two textures to draw this frame, by how it flashes.
=====================
*/
u16 *GetImageTexture(image_t *image, s32 lit) {
    u16 *result;

    if (lit != 0) {
        result = image->texture;
    } else {
        result = image->dimTexture;
    }
    if (image->flash == 1) {
        if (image->flashLeft > image->flashLit) {
            result = image->dimTexture;
        }
        image->flashLeft -= frameRetraces;
        if (image->flashLeft < 0) {
            image->flashLeft = image->flashFrames;
        }
    } else if (image->flash == 2) {
        result = image->dimTexture;
    }
    return result;
}

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
