#include "wof.h"

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
} Buffers;

typedef struct {
    /* 0x000 */ u8 unk_00[0x8];
    /* 0x008 */ s32 unk_08;
    /* 0x00C */ s32 unk_0C;
    /* 0x010 */ u8 unk_10[0x230];
    /* 0x240 */ s32 unk_240;
} Source;

s32 func_800A4C28(s32 arg0);

s32 func_80089984(s32 arg0, s32 arg1) {
    Buffers *buf;
    s32 sp14;
    s32 width;
    s32 height;
    s32 depth;
    s32 scale;

    sp14 = ((Source *)arg0)->unk_240;
    width = ((Source *)arg0)->unk_0C * 16;
    height = ((Source *)arg0)->unk_08 * 16;
    buf = (Buffers *)func_800A4C28(24);
    depth = 4;
    if (depth == 0) {
        depth = 1;
    }
    if (depth == 3) {
        depth = 4;
    }
    scale = 1;
    buf->unk_0C = func_800A4C28(width * height * depth * scale * scale);
    buf->unk_00 = func_800A4C28(width * height);
    buf->unk_04 = func_800A4C28((u32)(width * height) >> 2);
    buf->unk_08 = func_800A4C28((u32)(width * height) >> 2);
    buf->unk_10 = 0;
    return (s32)buf;
}
