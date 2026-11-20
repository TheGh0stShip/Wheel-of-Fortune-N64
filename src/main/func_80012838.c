#include "wof.h"


void func_80012838(tile_t *tiles, s32 count, s32 arg2) {
    s32 i;
    Gfx *gfx;

    if (D_800BCD54 != 6) {
        for (i = 0; i < count; i++) {
            if (arg2 != 0) {
                if (tiles[i].unk_04 == &D_010A2B88) {
                    func_80005300(2);
                    gfx = D_800B81E8++;
                    gfx->words.w0 = 0xE7000000;
                    gfx->words.w1 = 0;
                    gfx = D_800B81E8++;
                    gfx->words.w0 = 0x6000000;
                    gfx->words.w1 = tiles[i].unk_00;
                }
            } else if (tiles[i].unk_04 != &D_010A2B88) {
                gfx = D_800B81E8++;
                gfx->words.w0 = 0xBC00200A;
                gfx->words.w1 = func_8001277C(&tiles[i]);
                gfx = D_800B81E8++;
                gfx->words.w0 = 0xBC00240A;
                gfx->words.w1 = func_8001277C(&tiles[i]);
                gfx = D_800B81E8++;
                gfx->words.w0 = 0xE7000000;
                gfx->words.w1 = 0;
                gfx = D_800B81E8++;
                gfx->words.w0 = 0xFD900000;
                gfx->words.w1 = (s32)tiles[i].unk_04;
                gfx = D_800B81E8++;
                gfx->words.w0 = 0xF5900000;
                gfx->words.w1 = 0x7094250;
                gfx = D_800B81E8++;
                gfx->words.w0 = 0xE6000000;
                gfx->words.w1 = 0;
                gfx = D_800B81E8++;
                gfx->words.w0 = 0xF3000000;
                gfx->words.w1 = 0x71FF200;
                gfx = D_800B81E8++;
                gfx->words.w0 = 0xE7000000;
                gfx->words.w1 = 0;
                gfx = D_800B81E8++;
                gfx->words.w0 = 0xF5880800;
                gfx->words.w1 = 0x94250;
                gfx = D_800B81E8++;
                gfx->words.w0 = 0xF2000000;
                gfx->words.w1 = 0x7C07C;
                gfx = D_800B81E8++;
                gfx->words.w0 = 0xE7000000;
                gfx->words.w1 = 0;
                gfx = D_800B81E8++;
                gfx->words.w0 = 0x6000000;
                gfx->words.w1 = tiles[i].unk_00;
            }
        }
        return;
    }
    i = 0;
    while (i < count) {
        func_80005300(2);
        gfx = D_800B81E8++;
        gfx->words.w0 = 0xE7000000;
        gfx->words.w1 = 0;
        gfx = D_800B81E8++;
        gfx->words.w0 = 0x6000000;
        gfx->words.w1 = tiles[i].unk_00;
        i++;
    }
}
