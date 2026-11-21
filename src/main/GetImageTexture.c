#include "wof.h"

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
