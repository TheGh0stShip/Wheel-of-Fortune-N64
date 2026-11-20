#include "wof.h"

s32 func_80013440(layer_t *layer) {
    s32 result;

    result = layer->unk_10;
    if (layer->unk_04 != 0) {
        if (layer->unk_0C > layer->unk_08 / 2) {
            result = layer->unk_14;
        }
        layer->unk_0C = layer->unk_0C - D_800B96B4;
        if (layer->unk_0C < 0) {
            layer->unk_0C = layer->unk_08;
        }
    }
    return result;
}
