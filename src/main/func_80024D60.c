#include "wof.h"

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
} Preset;

extern Preset D_8005A3E4[];

void func_80024D60(s32 arg0) {
    D_800B9990[arg0].unk_110 = D_8005A3E4[D_800B9990[arg0].unk_018].unk_14;
    D_800B9990[arg0].unk_0FC = D_8005A3E4[D_800B9990[arg0].unk_018].unk_00;
    D_800B9990[arg0].unk_100 = D_8005A3E4[D_800B9990[arg0].unk_018].unk_04;
    D_800B9990[arg0].unk_104 = D_8005A3E4[D_800B9990[arg0].unk_018].unk_08;
    D_800B9990[arg0].unk_108 = D_8005A3E4[D_800B9990[arg0].unk_018].unk_0C;
    D_800B9990[arg0].unk_10C = D_8005A3E4[D_800B9990[arg0].unk_018].unk_10;
}
