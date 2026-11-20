#include "wof.h"

typedef struct {
    /* 0x00 */ u8 unk_00[0xC];
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ u8 unk_10[0x4];
    /* 0x14 */ s32 unk_14;
} Config;

typedef struct {
    /* 0x00 */ u8 unk_00[0x8];
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ u8 unk_18[0x24];
    /* 0x3C */ s32 unk_3C;
    /* 0x40 */ s32 unk_40;
} Scroll;

void func_800998E0(s32 arg0, s32 arg1, s32 arg2) {
    Config *cfg;
    Scroll *scroll;
    s32 sp8;
    s32 spC;
    s32 sp10;
    s32 sp14;
    s32 sp18;
    s32 sp1C;
    s32 max;
    s32 min;
    s32 sp28;

    cfg = (Config *)(arg2 + 204);
    scroll = (Scroll *)(arg2 + 264);
    if (cfg->unk_14 == 1 || scroll->unk_08 == 0) {
        sp8 = 0;
    } else {
        sp8 = cfg->unk_14 - 1 - scroll->unk_0C;
    }
    if (cfg->unk_14 == 1 || scroll->unk_10 == 0) {
        spC = 0;
    } else {
        spC = cfg->unk_14 - 1 - scroll->unk_14;
    }
    sp10 = scroll->unk_08 * cfg->unk_14;
    if (sp10 == 0) {
        sp14 = 0;
    } else if (sp10 > 0) {
        sp10 -= sp8;
        sp14 = sp10 - cfg->unk_14 * 32;
    } else {
        sp10 += sp8;
        sp14 = sp10 + cfg->unk_14 * 32;
    }
    sp18 = scroll->unk_10 * cfg->unk_14;
    if (sp18 == 0) {
        sp1C = 0;
    } else if (sp18 > 0) {
        sp18 -= spC;
        sp1C = sp18 - cfg->unk_14 * 32;
    } else {
        sp18 += spC;
        sp1C = sp18 + cfg->unk_14 * 32;
    }
    max = cfg->unk_14 * 16 - 1;
    min = cfg->unk_14 * -16;
    sp28 = scroll->unk_3C + sp10;
    if (sp28 <= max && sp28 >= min) {
        *(s32 *)arg0 = scroll->unk_3C + sp10;
    } else {
        *(s32 *)arg0 = scroll->unk_3C + sp14;
    }
    scroll->unk_3C = *(s32 *)arg0;
    if (cfg->unk_0C != 0) {
        *(s32 *)arg0 <<= 1;
    }
    sp28 = scroll->unk_40 + sp18;
    if (sp28 <= max && sp28 >= min) {
        *(s32 *)arg1 = scroll->unk_40 + sp18;
    } else {
        *(s32 *)arg1 = scroll->unk_40 + sp1C;
    }
    scroll->unk_40 = *(s32 *)arg1;
    if (cfg->unk_0C != 0) {
        *(s32 *)arg1 <<= 1;
    }
}
