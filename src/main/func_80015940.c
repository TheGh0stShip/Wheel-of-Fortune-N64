#include "wof.h"

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 *unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ s32 unk_18;
} Tile;

extern s32 D_010A1B88;
extern s32 D_010A1F88;
extern s32 D_010A2388;
extern s32 D_010A2788;
extern s32 D_010A2B88;
extern s32 D_010A3388;
extern s32 D_010A3788;
extern s32 D_800579BC[];
extern u8 D_800B9601[][21];

void func_80015940(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 i;

    for (i = 0; i < arg3; i++) {
        ((Tile *)arg1)[i].unk_00 = ((s32 *)arg0)[i];
        ((Tile *)arg1)[i].unk_0C = 0;
        ((Tile *)arg1)[i].unk_10 = 32;
        ((Tile *)arg1)[i].unk_14 = 0;
        switch (D_800B9601[arg2][i]) {
        case 0:
        case 32:
        case 47:
            ((Tile *)arg1)[i].unk_04 = &D_010A2B88;
            ((Tile *)arg1)[i].unk_18 = -1;
            break;
        case 38:
            ((Tile *)arg1)[i].unk_04 = &D_010A1F88;
            ((Tile *)arg1)[i].unk_18 = -1;
            break;
        case 46:
            ((Tile *)arg1)[i].unk_04 = &D_010A3788;
            ((Tile *)arg1)[i].unk_18 = -1;
            break;
        case 39:
            ((Tile *)arg1)[i].unk_04 = &D_010A2388;
            ((Tile *)arg1)[i].unk_18 = -1;
            break;
        case 45:
            ((Tile *)arg1)[i].unk_04 = &D_010A1B88;
            ((Tile *)arg1)[i].unk_18 = -1;
            break;
        case 63:
            ((Tile *)arg1)[i].unk_04 = &D_010A2788;
            ((Tile *)arg1)[i].unk_18 = -1;
            break;
        default:
            ((Tile *)arg1)[i].unk_04 = &D_010A3388;
            ((Tile *)arg1)[i].unk_08 = D_800579BC[D_800B9601[arg2][i]];
            ((Tile *)arg1)[i].unk_18 = 0x88888888;
        }
    }
}
