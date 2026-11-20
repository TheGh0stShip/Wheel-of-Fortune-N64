#include "wof.h"

extern s32 *D_800FF2DC;
extern s32 *D_800FF2E0;
extern s32 *D_800FF2E4;

void func_800A1BE4(s32 arg0) {
    s32 sp10;
    s32 sp14;
    s32 sp18;
    s32 pad0;
    s32 sp20;
    s32 sp24;
    s32 i;

    sp10 = D_80107480;
    sp14 = D_80107484;
    sp18 = D_80107488;
    D_800FF2C8 = (s32 *)func_800A4C28(1024);
    D_800FF2CC = (s32 *)func_800A4C28(1024);
    D_800FF2D0 = (s32 *)func_800A4C28(1024);
    D_800FF2D4 = (s32 *)func_800A4C28(1024);
    D_800FF2D8 = (s32 *)func_800A4C28(1024);
    D_800FF2E8 = (s32 *)func_800A4C28(3072);
    D_800FF2EC = (s32 *)func_800A4C28(3072);
    D_800FF2F0 = (s32 *)func_800A4C28(3072);
    for (i = 0; i < 256; i++) {
        switch (D_80086D3C) {
        case 1:
            D_800FF2C8[i] = D_80086D60[i];
            break;
        case 2:
            D_800FF2C8[i] = D_80087560[i];
            break;
        case 3:
            D_800FF2C8[i] = D_80087160[i];
            break;
        default:
            D_800FF2C8[i] = i;
        }
        sp24 = sp20 = i;
        if (D_80086D40 != 0) {
            sp24 -= 128;
            sp24 = (sp24 >= 0) ? ((((s32)(sp24 * D_80086D48)) >= 128) ? 127 : ((s32)(sp24 * D_80086D48))) : ((((s32)(sp24 * D_80086D48)) < -128) ? -128 : ((s32)(sp24 * D_80086D48)));
            sp20 -= 128;
            sp20 = (sp20 >= 0) ? ((((s32)(sp20 * D_80086D48)) >= 128) ? 127 : ((s32)(sp20 * D_80086D48))) : ((((s32)(sp20 * D_80086D48)) < -128) ? -128 : ((s32)(sp20 * D_80086D48)));
        } else {
            sp24 -= 128;
            sp20 -= 128;
        }
        D_800FF2CC[i] = sp20 * 1.4013377926421404;
        D_800FF2D0[i] = sp20 * -0.7136038186157518;
        D_800FF2D4[i] = sp24 * -0.34441087613293053;
        D_800FF2D8[i] = sp24 * 1.7734138972809665;
    }
    i = 0;
    while (i < 256) {
        D_800FF2E8[i + 256] = i >> (8 - func_800A19D8(sp10));
        D_800FF2E8[i + 256] = D_800FF2E8[i + 256] << func_800A1B60(sp10);
        D_800FF2EC[i + 256] = i >> (8 - func_800A19D8(sp14));
        D_800FF2EC[i + 256] = D_800FF2EC[i + 256] << func_800A1B60(sp14);
        D_800FF2F0[i + 256] = i >> (8 - func_800A19D8(sp18));
        D_800FF2F0[i + 256] = D_800FF2F0[i + 256] << func_800A1B60(sp18);
        if (arg0 == 0) {
            D_800FF2E8[i + 256] = D_800FF2E8[i + 256] | (D_800FF2E8[i + 256] << 16);
            D_800FF2EC[i + 256] = D_800FF2EC[i + 256] | (D_800FF2EC[i + 256] << 16);
            D_800FF2F0[i + 256] = D_800FF2F0[i + 256] | (D_800FF2F0[i + 256] << 16);
        }
        i++;
    }
    i = 0;
    while (i < 256) {
        D_800FF2E8[i] = D_800FF2E8[256];
        D_800FF2E8[i + 512] = D_800FF2E8[511];
        D_800FF2EC[i] = D_800FF2EC[256];
        D_800FF2EC[i + 512] = D_800FF2EC[511];
        D_800FF2F0[i] = D_800FF2F0[256];
        D_800FF2F0[i + 512] = D_800FF2F0[511];
        i++;
    }
    D_800FF2DC = &D_800FF2E8[256];
    D_800FF2E0 = &D_800FF2EC[256];
    D_800FF2E4 = &D_800FF2F0[256];
}
