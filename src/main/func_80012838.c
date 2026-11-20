#include "wof.h"


void func_80012838(tile_t *tiles, s32 count, s32 arg2) {
    s32 i;

    if (D_800BCD54 != 6) {
        for (i = 0; i < count; i++) {
            if (arg2 != 0) {
                if (tiles[i].unk_04 == D_010A2B88) {
                    func_80005300(2);
                    gDPPipeSync(D_800B81E8++);
                    gSPDisplayList(D_800B81E8++, tiles[i].unk_00);
                }
            } else if (tiles[i].unk_04 != D_010A2B88) {
                gSPLightColor(D_800B81E8++, LIGHT_2, func_8001277C(&tiles[i]));
                gDPPipeSync(D_800B81E8++);
                gDPLoadTextureBlock(D_800B81E8++, tiles[i].unk_04, G_IM_FMT_I, G_IM_SIZ_8b, 32, 32, 0,
                                    G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                                    5, 5, G_TX_NOLOD, G_TX_NOLOD);
                gDPPipeSync(D_800B81E8++);
                gSPDisplayList(D_800B81E8++, tiles[i].unk_00);
            }
        }
        return;
    }
    i = 0;
    while (i < count) {
        func_80005300(2);
        gDPPipeSync(D_800B81E8++);
        gSPDisplayList(D_800B81E8++, tiles[i].unk_00);
        i++;
    }
}
