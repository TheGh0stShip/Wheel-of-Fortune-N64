#include "wof.h"

typedef struct {
    /* 0x0000 */ u8 unk_0000[0x140];
    /* 0x0140 */ Mtx unk_0140[100];
    /* 0x1A40 */ Mtx unk_1A40[100];
    /* 0x3340 */ Mtx unk_3340[1];
} MtxBank;

typedef struct {
    /* 0x00 */ s32 index;
    /* 0x04 */ u8 unk_04[0xC];
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ u8 unk_16[0x2];
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ u8 unk_1C[0xC];
    /* 0x28 */ f32 unk_28;
    /* 0x2C */ f32 unk_2C;
    /* 0x30 */ f32 unk_30;
    /* 0x34 */ u8 unk_34[0x14];
    /* 0x48 */ s32 unk_48;
} Actor;

extern s32 D_010219C8;
extern Gfx *D_800B81E8;

void func_80014768(s32 arg0, s32 arg1) {
    Gfx *gfx;

    switch (func_80016638()) {
    case 0:
        func_8003C2F0((s32)&((MtxBank *)arg1)->unk_1A40[((Actor *)arg0)->index], ((Actor *)arg0)->unk_10,
                      ((Actor *)arg0)->unk_12, ((Actor *)arg0)->unk_14);
        func_8003C09C((s32)&((MtxBank *)arg1)->unk_0140[((Actor *)arg0)->index], ((Actor *)arg0)->unk_18,
                      ((Actor *)arg0)->unk_18, ((Actor *)arg0)->unk_18);
        func_8003BFF4((s32)&((MtxBank *)arg1)->unk_3340[((Actor *)arg0)->index], ((Actor *)arg0)->unk_28,
                      ((Actor *)arg0)->unk_2C, ((Actor *)arg0)->unk_30);
        gfx = D_800B81E8++;
        gfx->w0 = 0x1020040;
        gfx->w1 = (s32)&((MtxBank *)arg1)->unk_1A40[((Actor *)arg0)->index];
        gfx = D_800B81E8++;
        gfx->w0 = 0x1000040;
        gfx->w1 = (s32)&((MtxBank *)arg1)->unk_0140[((Actor *)arg0)->index];
        gfx = D_800B81E8++;
        gfx->w0 = 0x1000040;
        gfx->w1 = (s32)&((MtxBank *)arg1)->unk_3340[((Actor *)arg0)->index];
        gfx = D_800B81E8++;
        gfx->w0 = 0x6000000;
        gfx->w1 = (s32)&D_010219C8;
        gfx = D_800B81E8++;
        gfx->w0 = 0xBC00000A;
        gfx->w1 = 0xC8C8C8FF;
        gfx = D_800B81E8++;
        gfx->w0 = 0xBC00040A;
        gfx->w1 = 0xC8C8C8FF;
        gfx = D_800B81E8++;
        gfx->w0 = 0x6000000;
        gfx->w1 = ((Actor *)arg0)->unk_48;
        func_80005300(1);
    }
}
