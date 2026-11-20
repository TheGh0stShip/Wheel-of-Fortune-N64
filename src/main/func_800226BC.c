#include "wof.h"

void func_800226BC(image_t *images, s32 count, s32 arg2) {
    s32 i;

    for (i = 0; i < count; i++) {
        images[i].unk_10 = arg2;
        images[i].unk_1C = images[i].unk_14;
    }
}
