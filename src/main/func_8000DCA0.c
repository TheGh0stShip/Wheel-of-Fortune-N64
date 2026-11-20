#include "wof.h"

typedef struct {
    /* 0x0000 */ u8 unk_0000[0x3340];
    /* 0x3340 */ Mtx unk_3340[1];
} MtxBank;

extern Gfx *D_800B81E8;

void func_8000DCA0(s32 arg0, s32 arg1) {
    Gfx *gfx;

    if (D_800B3994 < 318) {
        return;
    }
    ((obj_t *)arg0)->unk_2C += (f32)(D_800B96B4 * 2);
    guRotateRPY((s32)&((MtxBank *)arg1)->unk_3340[((obj_t *)arg0)->index], ((obj_t *)arg0)->unk_28,
                  ((obj_t *)arg0)->unk_2C, ((obj_t *)arg0)->unk_30);
    gfx = D_800B81E8++;
    gfx->words.w0 = 0x1020040;
    gfx->words.w1 = (s32)&D_01176C88;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0x1000040;
    gfx->words.w1 = (s32)&((MtxBank *)arg1)->unk_3340[((obj_t *)arg0)->index];
    gfx = D_800B81E8++;
    gfx->words.w0 = 0x6000000;
    gfx->words.w1 = (s32)&D_01166928;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0x1020040;
    gfx->words.w1 = (s32)&D_01176CC8;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0x1000040;
    gfx->words.w1 = (s32)&((MtxBank *)arg1)->unk_3340[((obj_t *)arg0)->index];
    gfx = D_800B81E8++;
    gfx->words.w0 = 0x6000000;
    gfx->words.w1 = (s32)&D_01166598;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xE7000000;
    gfx->words.w1 = 0;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xB900031D;
    gfx->words.w1 = 0x552078;
}
