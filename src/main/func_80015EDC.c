#include "wof.h"

void func_80015EDC(s32 *arg0, tile_t *tiles, s32 row, s32 count) {
    s32 i;

    for (i = 0; i < count; i++) {
        tiles[i].unk_00 = arg0[i];
        tiles[i].unk_0C = 0;
        tiles[i].unk_10 = 32;
        tiles[i].unk_14 = 0;
        tiles[i].unk_04 = D_010A2B88;
    }
}
