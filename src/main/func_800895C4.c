#include "wof.h"

typedef struct {
    /* 0x000 */ u8 unk_000[0x20];
    /* 0x020 */ s8 unk_020[8][8];
    /* 0x060 */ s8 unk_060[8][8];
    /* 0x0A0 */ s32 unk_0A0;
    /* 0x0A4 */ s32 unk_0A4;
    /* 0x0A8 */ u8 unk_0A8[0x1C];
    /* 0x0C4 */ s32 unk_0C4;
    /* 0x0C8 */ s32 unk_0C8;
    /* 0x0CC */ u8 unk_0CC[0x24];
    /* 0x0F0 */ s32 unk_0F0;
    /* 0x0F4 */ s32 unk_0F4;
    /* 0x0F8 */ s32 unk_0F8;
    /* 0x0FC */ u8 unk_0FC[0x8];
    /* 0x104 */ s32 unk_104;
    /* 0x108 */ u8 unk_108[0xD8];
    /* 0x1E0 */ s32 unk_1E0;
    /* 0x1E4 */ s32 unk_1E4;
    /* 0x1E8 */ s32 unk_1E8;
    /* 0x1EC */ s32 unk_1EC;
    /* 0x1F0 */ s32 unk_1F0;
    /* 0x1F4 */ s32 unk_1F4;
    /* 0x1F8 */ u8 unk_1F8[0xC];
    /* 0x204 */ s32 unk_204;
    /* 0x208 */ u8 unk_208[0x34];
    /* 0x23C */ s32 unk_23C;
    /* 0x240 */ u8 unk_240[0x4];
    /* 0x244 */ s32 unk_244;
    /* 0x248 */ s32 unk_248;
    /* 0x24C */ u8 unk_24C[0xC];
    /* 0x258 */ s32 unk_258;
    /* 0x25C */ s32 unk_25C;
    /* 0x260 */ s32 unk_260;
    /* 0x264 */ s32 unk_264[5];
} Decoder;

extern u8 D_80087EA0[];

s32 func_800895C4(s32 arg0) {
    s32 i;
    s32 j;
    Decoder *dec;

    if ((u32)arg0 < 4) {
        return 0;
    }
    arg0 = (u32)(arg0 + 3) >> 2;
    dec = (Decoder *)func_800A4C28(632);
    dec->unk_0C4 = dec->unk_0C8 = dec->unk_0F0 = dec->unk_0F8 = dec->unk_0F4 = dec->unk_104 = dec->unk_0A0 = dec->unk_0A4 = 0;
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            dec->unk_020[i][j] = D_80087EA0[i * 8 + j];
        }
    }
    i = 0;
    while (i < 8) {
        for (j = 0; j < 8; j++) {
            dec->unk_060[i][j] = 16;
        }
        i++;
    }
    dec->unk_260 = dec->unk_258 = dec->unk_25C = 0;
    for (i = 0; i < 5; i++) {
        dec->unk_264[i] = 0;
    }
    dec->unk_1EC = func_800A4C28(arg0 * 4);
    dec->unk_1F0 = arg0 - 1;
    dec->unk_1E0 = 0;
    dec->unk_1E8 = 0;
    dec->unk_1E4 = dec->unk_1EC;
    dec->unk_1F4 = 0;
    dec->unk_23C = 0;
    dec->unk_248 = 0;
    dec->unk_244 = 0;
    dec->unk_204 = 0;
    return (s32)dec;
}
