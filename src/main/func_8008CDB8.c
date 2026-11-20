#include "wof.h"

typedef struct {
    /* 0x000 */ u8 unk_000[0xC];
    /* 0x00C */ s32 unk_00C;
    /* 0x010 */ u8 unk_010[0xEC];
    /* 0x0FC */ s32 unk_0FC;
    /* 0x100 */ s32 unk_100;
    /* 0x104 */ s32 unk_104;
    /* 0x108 */ s32 unk_108;
    /* 0x10C */ u8 unk_10C[0x34];
    /* 0x140 */ s32 unk_140;
    /* 0x144 */ s32 unk_144;
    /* 0x148 */ s32 unk_148;
    /* 0x14C */ s32 unk_14C;
    /* 0x150 */ s32 unk_150;
    /* 0x154 */ u8 unk_154[0x80];
    /* 0x1D4 */ s16 unk_1D4;
    /* 0x1D6 */ s16 unk_1D6;
    /* 0x1D8 */ s16 unk_1D8;
    /* 0x1DC */ u8 unk_1DC[0x4];
    /* 0x1E0 */ s32 bitPos;
    /* 0x1E4 */ s32 *src;
    /* 0x1E8 */ s32 srcLeft;
    /* 0x1EC */ u8 unk_1EC[0x48];
    /* 0x234 */ s32 bits;
} Decoder;

void func_800887D8(s32 arg0);
s32 func_800890C8(s32 arg0);
void func_800A4C04(s32 arg0);

s32 func_8008CDB8(s32 arg0) {
    s32 sp10;

    if (arg0 == 0) {
        /* empty */
    }
    if (((Decoder *)arg0)->srcLeft < 2) {
        func_800887D8(arg0);
    }
    ((Decoder *)arg0)->bitPos = ((Decoder *)arg0)->bitPos + 24;
    if ((((Decoder *)arg0)->bitPos & 32) != 0) {
        ((Decoder *)arg0)->srcLeft--;
        ((Decoder *)arg0)->bitPos = ((Decoder *)arg0)->bitPos - 32;
        ((Decoder *)arg0)->src++;
        ((Decoder *)arg0)->bits = *((Decoder *)arg0)->src << ((Decoder *)arg0)->bitPos;
    } else {
        ((Decoder *)arg0)->bits = ((Decoder *)arg0)->bits << 24;
    }
    if (((Decoder *)arg0)->srcLeft < 2) {
        func_800887D8(arg0);
    }
    ((Decoder *)arg0)->bitPos = ((Decoder *)arg0)->bitPos + 8;
    if ((((Decoder *)arg0)->bitPos & 32) != 0) {
        ((Decoder *)arg0)->bitPos = ((Decoder *)arg0)->bitPos - 32;
        ((Decoder *)arg0)->src++;
        ((Decoder *)arg0)->srcLeft--;
        if (((Decoder *)arg0)->bitPos != 0) {
            ((Decoder *)arg0)->bits = ((Decoder *)arg0)->bits | ((u32)*((Decoder *)arg0)->src >> (8 - ((Decoder *)arg0)->bitPos));
        }
        sp10 = (u32)(((Decoder *)arg0)->bits & 0xFF000000) >> 24;
        ((Decoder *)arg0)->bits = *((Decoder *)arg0)->src << ((Decoder *)arg0)->bitPos;
    } else {
        sp10 = (u32)(((Decoder *)arg0)->bits & 0xFF000000) >> 24;
        ((Decoder *)arg0)->bits = ((Decoder *)arg0)->bits << 8;
    }
    ((Decoder *)arg0)->unk_0FC = sp10;
    if (((Decoder *)arg0)->srcLeft < 2) {
        func_800887D8(arg0);
    }
    ((Decoder *)arg0)->bitPos = ((Decoder *)arg0)->bitPos + 5;
    if ((((Decoder *)arg0)->bitPos & 32) != 0) {
        ((Decoder *)arg0)->bitPos = ((Decoder *)arg0)->bitPos - 32;
        ((Decoder *)arg0)->src++;
        ((Decoder *)arg0)->srcLeft--;
        if (((Decoder *)arg0)->bitPos != 0) {
            ((Decoder *)arg0)->bits = ((Decoder *)arg0)->bits | ((u32)*((Decoder *)arg0)->src >> (5 - ((Decoder *)arg0)->bitPos));
        }
        sp10 = (u32)(((Decoder *)arg0)->bits & 0xF8000000) >> 27;
        ((Decoder *)arg0)->bits = *((Decoder *)arg0)->src << ((Decoder *)arg0)->bitPos;
    } else {
        sp10 = (u32)(((Decoder *)arg0)->bits & 0xF8000000) >> 27;
        ((Decoder *)arg0)->bits = ((Decoder *)arg0)->bits << 5;
    }
    ((Decoder *)arg0)->unk_100 = sp10;
    if (((Decoder *)arg0)->unk_104 != 0) {
        func_800A4C04(((Decoder *)arg0)->unk_104);
        ((Decoder *)arg0)->unk_104 = 0;
    }
    ((Decoder *)arg0)->unk_104 = func_800890C8(arg0);
    ((Decoder *)arg0)->unk_140 = -2;
    ((Decoder *)arg0)->unk_144 = 0;
    ((Decoder *)arg0)->unk_148 = 0;
    ((Decoder *)arg0)->unk_14C = 0;
    ((Decoder *)arg0)->unk_150 = 0;
    ((Decoder *)arg0)->unk_108 = ((((Decoder *)arg0)->unk_0FC - 1) * ((Decoder *)arg0)->unk_00C) - 1;
    ((Decoder *)arg0)->unk_1D4 = 0x2000;
    ((Decoder *)arg0)->unk_1D6 = 0x2000;
    ((Decoder *)arg0)->unk_1D8 = 0x2000;
    return 1;
}
