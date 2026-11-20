#include "wof.h"

u16 *func_8002731C(image_t *image, s32 arg1) {
    u16 *result;

    if (arg1 != 0) {
        result = image->unk_20;
    } else {
        result = image->unk_24;
    }
    if (image->unk_10 == 1) {
        if (image->unk_1C > image->unk_18) {
            result = image->unk_24;
        }
        image->unk_1C -= frameRetraces;
        if (image->unk_1C < 0) {
            image->unk_1C = image->unk_14;
        }
    } else if (image->unk_10 == 2) {
        result = image->unk_24;
    }
    return result;
}
