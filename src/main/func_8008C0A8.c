#include "wof.h"

typedef struct {
    /* 0x00 */ u8 unk_00[0x10];
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
} Buf;

typedef struct {
    /* 0x000 */ u8 unk_000[0xBC];
    /* 0x0BC */ s32 unk_0BC;
    /* 0x0C0 */ u8 unk_0C0[0xC];
    /* 0x0CC */ s32 unk_0CC;
    /* 0x0D0 */ s32 unk_0D0;
    /* 0x0D4 */ s32 unk_0D4;
    /* 0x0D8 */ s32 unk_0D8;
    /* 0x0DC */ s32 unk_0DC;
    /* 0x0E0 */ s32 unk_0E0;
    /* 0x0E4 */ s32 unk_0E4;
    /* 0x0E8 */ s32 unk_0E8;
    /* 0x0EC */ s32 unk_0EC;
    /* 0x0F0 */ s32 unk_0F0;
    /* 0x0F4 */ s32 unk_0F4;
    /* 0x0F8 */ s32 unk_0F8;
    /* 0x0FC */ u8 unk_0FC[0x10];
    /* 0x10C */ s32 unk_10C;
    /* 0x110 */ u8 unk_110[0xD0];
    /* 0x1E0 */ s32 pos;
    /* 0x1E4 */ u32 *ptr;
    /* 0x1E8 */ s32 words;
    /* 0x1EC */ u8 unk_1EC[0x48];
    /* 0x234 */ u32 bits;
    /* 0x238 */ u8 unk_238[0x20];
    /* 0x258 */ s32 unk_258;
    /* 0x25C */ s32 unk_25C;
    /* 0x260 */ Buf *cur;
    /* 0x264 */ Buf *bufs[5];
} Ctx;

extern s32 D_80085308;
extern s32 D_8008530C;
extern s32 D_80087EE0;

s32 func_8008C0A8(s32 arg0, s32 arg1) {
    s32 value;
    s32 i;

    if (arg0 == 0) {
    }
    if (((Ctx *)arg0)->words < 2) {
        func_800887D8(arg0);
    }
    ((Ctx *)arg0)->ptr++;
    ((Ctx *)arg0)->words--;
    ((Ctx *)arg0)->bits = *((Ctx *)arg0)->ptr << ((Ctx *)arg0)->pos;
    if (((Ctx *)arg0)->words < 2) {
        func_800887D8(arg0);
    }
    ((Ctx *)arg0)->pos += 10;
    if ((((Ctx *)arg0)->pos & 32) != 0) {
        ((Ctx *)arg0)->pos -= 32;
        ((Ctx *)arg0)->ptr++;
        ((Ctx *)arg0)->words--;
        if (((Ctx *)arg0)->pos != 0) {
            ((Ctx *)arg0)->bits |= *((Ctx *)arg0)->ptr >> (10 - ((Ctx *)arg0)->pos);
        }
        value = (((Ctx *)arg0)->bits & 0xFFC00000) >> 22;
        ((Ctx *)arg0)->bits = *((Ctx *)arg0)->ptr << ((Ctx *)arg0)->pos;
    } else {
        value = (((Ctx *)arg0)->bits & 0xFFC00000) >> 22;
        ((Ctx *)arg0)->bits <<= 10;
    }
    ((Ctx *)arg0)->unk_0CC = value;
    if (((Ctx *)arg0)->words < 2) {
        func_800887D8(arg0);
    }
    ((Ctx *)arg0)->pos += 3;
    if ((((Ctx *)arg0)->pos & 32) != 0) {
        ((Ctx *)arg0)->pos -= 32;
        ((Ctx *)arg0)->ptr++;
        ((Ctx *)arg0)->words--;
        if (((Ctx *)arg0)->pos != 0) {
            ((Ctx *)arg0)->bits |= *((Ctx *)arg0)->ptr >> (3 - ((Ctx *)arg0)->pos);
        }
        value = (((Ctx *)arg0)->bits & 0xE0000000) >> 29;
        ((Ctx *)arg0)->bits = *((Ctx *)arg0)->ptr << ((Ctx *)arg0)->pos;
    } else {
        value = (((Ctx *)arg0)->bits & 0xE0000000) >> 29;
        ((Ctx *)arg0)->bits <<= 3;
    }
    ((Ctx *)arg0)->unk_0D0 = value;
    if ((((Ctx *)arg0)->unk_0D0 == 3) && ((D_8008530C != 0) || ((((Ctx *)arg0)->unk_25C == 0) || ((((Ctx *)arg0)->unk_258 == 0) && (((Ctx *)arg0)->unk_0BC == 0))))) {
        return -10;
    }
    if ((((Ctx *)arg0)->unk_0D0 == 2) && ((D_80085308 != 0) || (((Ctx *)arg0)->unk_25C == 0))) {
        return -10;
    }
    if (((Ctx *)arg0)->words < 2) {
        func_800887D8(arg0);
    }
    ((Ctx *)arg0)->pos += 16;
    if ((((Ctx *)arg0)->pos & 32) != 0) {
        ((Ctx *)arg0)->pos -= 32;
        ((Ctx *)arg0)->ptr++;
        ((Ctx *)arg0)->words--;
        if (((Ctx *)arg0)->pos != 0) {
            ((Ctx *)arg0)->bits |= *((Ctx *)arg0)->ptr >> (16 - ((Ctx *)arg0)->pos);
        }
        value = (((Ctx *)arg0)->bits & 0xFFFF0000) >> 16;
        ((Ctx *)arg0)->bits = *((Ctx *)arg0)->ptr << ((Ctx *)arg0)->pos;
    } else {
        value = (((Ctx *)arg0)->bits & 0xFFFF0000) >> 16;
        ((Ctx *)arg0)->bits <<= 16;
    }
    ((Ctx *)arg0)->unk_0D4 = value;
    if ((((Ctx *)arg0)->unk_0D0 == 2) || (((Ctx *)arg0)->unk_0D0 == 3)) {
        if (((Ctx *)arg0)->words < 2) {
            func_800887D8(arg0);
        }
        value = ((Ctx *)arg0)->bits >> 31;
        ((Ctx *)arg0)->bits <<= 1;
        ((Ctx *)arg0)->pos++;
        if ((((Ctx *)arg0)->pos & 32) != 0) {
            ((Ctx *)arg0)->pos = 0;
            ((Ctx *)arg0)->ptr++;
            ((Ctx *)arg0)->bits = *((Ctx *)arg0)->ptr;
            ((Ctx *)arg0)->words--;
        }
        if (value != 0) {
            ((Ctx *)arg0)->unk_0D8 = 1;
        } else {
            ((Ctx *)arg0)->unk_0D8 = 0;
        }
        if (((Ctx *)arg0)->words < 2) {
            func_800887D8(arg0);
        }
        ((Ctx *)arg0)->pos += 3;
        if ((((Ctx *)arg0)->pos & 32) != 0) {
            ((Ctx *)arg0)->pos -= 32;
            ((Ctx *)arg0)->ptr++;
            ((Ctx *)arg0)->words--;
            if (((Ctx *)arg0)->pos != 0) {
                ((Ctx *)arg0)->bits |= *((Ctx *)arg0)->ptr >> (3 - ((Ctx *)arg0)->pos);
            }
            value = (((Ctx *)arg0)->bits & 0xE0000000) >> 29;
            ((Ctx *)arg0)->bits = *((Ctx *)arg0)->ptr << ((Ctx *)arg0)->pos;
        } else {
            value = (((Ctx *)arg0)->bits & 0xE0000000) >> 29;
            ((Ctx *)arg0)->bits <<= 3;
        }
        ((Ctx *)arg0)->unk_0DC = value - 1;
        ((Ctx *)arg0)->unk_0E0 = 1 << ((Ctx *)arg0)->unk_0DC;
    }
    if (((Ctx *)arg0)->unk_0D0 == 3) {
        if (((Ctx *)arg0)->words < 2) {
            func_800887D8(arg0);
        }
        value = ((Ctx *)arg0)->bits >> 31;
        ((Ctx *)arg0)->bits <<= 1;
        ((Ctx *)arg0)->pos++;
        if ((((Ctx *)arg0)->pos & 32) != 0) {
            ((Ctx *)arg0)->pos = 0;
            ((Ctx *)arg0)->ptr++;
            ((Ctx *)arg0)->bits = *((Ctx *)arg0)->ptr;
            ((Ctx *)arg0)->words--;
        }
        if (value != 0) {
            ((Ctx *)arg0)->unk_0E4 = 1;
        } else {
            ((Ctx *)arg0)->unk_0E4 = 0;
        }
        if (((Ctx *)arg0)->words < 2) {
            func_800887D8(arg0);
        }
        ((Ctx *)arg0)->pos += 3;
        if ((((Ctx *)arg0)->pos & 32) != 0) {
            ((Ctx *)arg0)->pos -= 32;
            ((Ctx *)arg0)->ptr++;
            ((Ctx *)arg0)->words--;
            if (((Ctx *)arg0)->pos != 0) {
                ((Ctx *)arg0)->bits |= *((Ctx *)arg0)->ptr >> (3 - ((Ctx *)arg0)->pos);
            }
            value = (((Ctx *)arg0)->bits & 0xE0000000) >> 29;
            ((Ctx *)arg0)->bits = *((Ctx *)arg0)->ptr << ((Ctx *)arg0)->pos;
        } else {
            value = (((Ctx *)arg0)->bits & 0xE0000000) >> 29;
            ((Ctx *)arg0)->bits <<= 3;
        }
        ((Ctx *)arg0)->unk_0E8 = value - 1;
        ((Ctx *)arg0)->unk_0EC = 1 << ((Ctx *)arg0)->unk_0E8;
    }
    if (((Ctx *)arg0)->unk_0F0 != 0) {
        func_800A4C04(((Ctx *)arg0)->unk_0F0);
        ((Ctx *)arg0)->unk_0F0 = 0;
    }
    ((Ctx *)arg0)->unk_0F0 = func_800890C8(arg0);
    func_80088C58(arg0);
    if (func_800888C0(32, 437, arg0) != 0) {
        if (arg0 == 0) {
        }
        if (((Ctx *)arg0)->words < 2) {
            func_800887D8(arg0);
        }
        ((Ctx *)arg0)->ptr++;
        ((Ctx *)arg0)->words--;
        ((Ctx *)arg0)->bits = *((Ctx *)arg0)->ptr << ((Ctx *)arg0)->pos;
        if (((Ctx *)arg0)->unk_0F4 != 0) {
            func_800A4C04(((Ctx *)arg0)->unk_0F4);
            ((Ctx *)arg0)->unk_0F4 = 0;
        }
        ((Ctx *)arg0)->unk_0F4 = func_80088A2C(arg0);
    }
    if (func_800888C0(32, 434, arg0) != 0) {
        if (arg0 == 0) {
        }
        if (((Ctx *)arg0)->words < 2) {
            func_800887D8(arg0);
        }
        ((Ctx *)arg0)->ptr++;
        ((Ctx *)arg0)->words--;
        ((Ctx *)arg0)->bits = *((Ctx *)arg0)->ptr << ((Ctx *)arg0)->pos;
        if (((Ctx *)arg0)->unk_0F8 != 0) {
            func_800A4C04(((Ctx *)arg0)->unk_0F8);
            ((Ctx *)arg0)->unk_0F8 = 0;
        }
        ((Ctx *)arg0)->unk_0F8 = func_80088A2C(arg0);
    }
    i = 0;
    while (((Ctx *)arg0)->bufs[i]->unk_10 != 0) {
        if ((++i) >= 5) {
            func_80009F38(&D_80087EE0);
            func_800A4CBC(1);
        }
    }
    ((Ctx *)arg0)->cur = ((Ctx *)arg0)->bufs[i];
    ((Ctx *)arg0)->cur->unk_14 = arg1;
    ((Ctx *)arg0)->unk_10C = -1;
    return 1;
}
