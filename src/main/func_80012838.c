#include "wof.h"

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 *unk_04;
    /* 0x08 */ u8 unk_08[0x14];
} Tile;

extern Gfx *D_800B81E8;
s32 func_8001277C(s32 arg0);

void func_80012838(s32 arg0, s32 arg1, s32 arg2) {
    s32 i;
    Gfx *gfx;

    if (D_800BCD54 != 6) {
        for (i = 0; i < arg1; i++) {
            if (arg2 != 0) {
                if (((Tile *)arg0)[i].unk_04 == &D_010A2B88) {
                    func_80005300(2);
                    gfx = D_800B81E8++;
                    gfx->w0 = 0xE7000000;
                    gfx->w1 = 0;
                    gfx = D_800B81E8++;
                    gfx->w0 = 0x6000000;
                    gfx->w1 = ((Tile *)arg0)[i].unk_00;
                }
            } else if (((Tile *)arg0)[i].unk_04 != &D_010A2B88) {
                gfx = D_800B81E8++;
                gfx->w0 = 0xBC00200A;
                gfx->w1 = func_8001277C((s32)&((Tile *)arg0)[i]);
                gfx = D_800B81E8++;
                gfx->w0 = 0xBC00240A;
                gfx->w1 = func_8001277C((s32)&((Tile *)arg0)[i]);
                gfx = D_800B81E8++;
                gfx->w0 = 0xE7000000;
                gfx->w1 = 0;
                gfx = D_800B81E8++;
                gfx->w0 = 0xFD900000;
                gfx->w1 = (s32)((Tile *)arg0)[i].unk_04;
                gfx = D_800B81E8++;
                gfx->w0 = 0xF5900000;
                gfx->w1 = 0x7094250;
                gfx = D_800B81E8++;
                gfx->w0 = 0xE6000000;
                gfx->w1 = 0;
                gfx = D_800B81E8++;
                gfx->w0 = 0xF3000000;
                gfx->w1 = 0x71FF200;
                gfx = D_800B81E8++;
                gfx->w0 = 0xE7000000;
                gfx->w1 = 0;
                gfx = D_800B81E8++;
                gfx->w0 = 0xF5880800;
                gfx->w1 = 0x94250;
                gfx = D_800B81E8++;
                gfx->w0 = 0xF2000000;
                gfx->w1 = 0x7C07C;
                gfx = D_800B81E8++;
                gfx->w0 = 0xE7000000;
                gfx->w1 = 0;
                gfx = D_800B81E8++;
                gfx->w0 = 0x6000000;
                gfx->w1 = ((Tile *)arg0)[i].unk_00;
            }
        }
        return;
    }
    i = 0;
    while (i < arg1) {
        func_80005300(2);
        gfx = D_800B81E8++;
        gfx->w0 = 0xE7000000;
        gfx->w1 = 0;
        gfx = D_800B81E8++;
        gfx->w0 = 0x6000000;
        gfx->w1 = ((Tile *)arg0)[i].unk_00;
        i++;
    }
}
