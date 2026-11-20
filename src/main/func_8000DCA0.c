#include "wof.h"

typedef struct {
    /* 0x0000 */ u8 unk_0000[0x3340];
    /* 0x3340 */ Mtx unk_3340[1];
} MtxBank;

typedef struct {
    /* 0x00 */ s32 index;
    /* 0x04 */ u8 unk_04[0x24];
    /* 0x28 */ f32 unk_28;
    /* 0x2C */ f32 unk_2C;
    /* 0x30 */ f32 unk_30;
} Actor;

extern s32 D_01166598;
extern s32 D_01166928;
extern s32 D_01176C88;
extern s32 D_01176CC8;
extern s32 D_800B3994;
extern Gfx *D_800B81E8;
extern s32 D_800B96B4;

void func_8000DCA0(s32 arg0, s32 arg1) {
    Gfx *gfx;

    if (D_800B3994 < 318) {
        return;
    }
    ((Actor *)arg0)->unk_2C += (f32)(D_800B96B4 * 2);
    func_8003BFF4((s32)&((MtxBank *)arg1)->unk_3340[((Actor *)arg0)->index], ((Actor *)arg0)->unk_28,
                  ((Actor *)arg0)->unk_2C, ((Actor *)arg0)->unk_30);
    gfx = D_800B81E8++;
    gfx->w0 = 0x1020040;
    gfx->w1 = (s32)&D_01176C88;
    gfx = D_800B81E8++;
    gfx->w0 = 0x1000040;
    gfx->w1 = (s32)&((MtxBank *)arg1)->unk_3340[((Actor *)arg0)->index];
    gfx = D_800B81E8++;
    gfx->w0 = 0x6000000;
    gfx->w1 = (s32)&D_01166928;
    gfx = D_800B81E8++;
    gfx->w0 = 0x1020040;
    gfx->w1 = (s32)&D_01176CC8;
    gfx = D_800B81E8++;
    gfx->w0 = 0x1000040;
    gfx->w1 = (s32)&((MtxBank *)arg1)->unk_3340[((Actor *)arg0)->index];
    gfx = D_800B81E8++;
    gfx->w0 = 0x6000000;
    gfx->w1 = (s32)&D_01166598;
    gfx = D_800B81E8++;
    gfx->w0 = 0xE7000000;
    gfx->w1 = 0;
    gfx = D_800B81E8++;
    gfx->w0 = 0xB900031D;
    gfx->w1 = 0x552078;
}
