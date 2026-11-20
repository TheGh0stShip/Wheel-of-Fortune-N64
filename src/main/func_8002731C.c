#include "wof.h"

s32 func_8002731C(image_t *image, s32 arg1) {
    s32 result;

    if (arg1 != 0) {
        result = image->unk_20;
    } else {
        result = image->unk_24;
    }
    if (image->unk_10 == 1) {
        if (image->unk_1C > image->unk_18) {
            result = image->unk_24;
        }
        image->unk_1C -= D_800B96B4;
        if (image->unk_1C < 0) {
            image->unk_1C = image->unk_14;
        }
    } else if (image->unk_10 == 2) {
        result = image->unk_24;
    }
    return result;
}
