#include "wof.h"


void func_80015940(Gfx **arg0, tile_t *tiles, s32 row, s32 count) {
    s32 i;

    for (i = 0; i < count; i++) {
        tiles[i].unk_00 = arg0[i];
        tiles[i].unk_0C = 0;
        tiles[i].unk_10 = 32;
        tiles[i].unk_14 = 0;
        switch (D_800B9601[row][i]) {
        case 0:
        case 32:
        case 47:
            tiles[i].unk_04 = D_010A2B88;
            tiles[i].unk_18 = -1;
            break;
        case 38:
            tiles[i].unk_04 = D_010A1F88;
            tiles[i].unk_18 = -1;
            break;
        case 46:
            tiles[i].unk_04 = D_010A3788;
            tiles[i].unk_18 = -1;
            break;
        case 39:
            tiles[i].unk_04 = D_010A2388;
            tiles[i].unk_18 = -1;
            break;
        case 45:
            tiles[i].unk_04 = D_010A1B88;
            tiles[i].unk_18 = -1;
            break;
        case 63:
            tiles[i].unk_04 = D_010A2788;
            tiles[i].unk_18 = -1;
            break;
        default:
            tiles[i].unk_04 = D_010A3388;
            tiles[i].unk_08 = D_800579BC[D_800B9601[row][i]];
            tiles[i].unk_18 = 0x88888888;
        }
    }
}
