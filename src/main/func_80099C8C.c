#include "wof.h"
#include "mpeg/proto.h"

typedef struct {
    /* 0x00 */ u8 unk_00[0x18];
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ u8 unk_1C[0x4];
    /* 0x20 */ s32 unk_20;
} Mode;

typedef struct {
    /* 0x00 */ u8 unk_00[0x18];
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ s32 unk_24;
    /* 0x28 */ u8 unk_28[0x1C];
    /* 0x44 */ s32 unk_44;
    /* 0x48 */ s32 unk_48;
} Scroll;

void func_80099C8C(s32 arg0, s32 arg1, s32 arg2) {
    Mode *mode;
    Scroll *scroll;
    s32 sp8;
    s32 spC;
    s32 sp10;
    s32 sp14;
    s32 sp18;
    s32 sp1C;
    s32 max;
    s32 min;
    s32 pos;

    mode = (Mode *)(arg2 + 204);
    scroll = (Scroll *)(arg2 + 264);
    if (mode->unk_20 == 1 || scroll->unk_18 == 0) {
        sp8 = 0;
    } else {
        sp8 = mode->unk_20 - 1 - scroll->unk_1C;
    }
    if (mode->unk_20 == 1 || scroll->unk_20 == 0) {
        spC = 0;
    } else {
        spC = mode->unk_20 - 1 - scroll->unk_24;
    }
    sp10 = scroll->unk_18 * mode->unk_20;
    if (sp10 == 0) {
        sp14 = 0;
    } else if (sp10 > 0) {
        sp10 = sp10 - sp8;
        sp14 = sp10 - mode->unk_20 * 32;
    } else {
        sp10 = sp10 + sp8;
        sp14 = sp10 + mode->unk_20 * 32;
    }
    sp18 = scroll->unk_20 * mode->unk_20;
    if (sp18 == 0) {
        sp1C = 0;
    } else if (sp18 > 0) {
        sp18 = sp18 - spC;
        sp1C = sp18 - mode->unk_20 * 32;
    } else {
        sp18 = sp18 + spC;
        sp1C = sp18 + mode->unk_20 * 32;
    }
    max = mode->unk_20 * 16 - 1;
    min = mode->unk_20 * -16;
    pos = scroll->unk_44 + sp10;
    if (pos <= max && pos >= min) {
        *(s32 *)arg0 = scroll->unk_44 + sp10;
    } else {
        *(s32 *)arg0 = scroll->unk_44 + sp14;
    }
    scroll->unk_44 = *(s32 *)arg0;
    if (mode->unk_18 != 0) {
        *(s32 *)arg0 = *(s32 *)arg0 << 1;
    }
    pos = scroll->unk_48 + sp18;
    if (pos <= max && pos >= min) {
        *(s32 *)arg1 = scroll->unk_48 + sp18;
    } else {
        *(s32 *)arg1 = scroll->unk_48 + sp1C;
    }
    scroll->unk_48 = *(s32 *)arg1;
    if (mode->unk_18 != 0) {
        *(s32 *)arg1 = *(s32 *)arg1 << 1;
    }
}
