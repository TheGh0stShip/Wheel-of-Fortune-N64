#include "wof.h"
#include "mpeg/proto.h"

typedef struct {
    /* 0x000 */ s32 unk_000;
    /* 0x004 */ s32 unk_004;
    /* 0x008 */ s32 unk_008;
    /* 0x00C */ s32 unk_00C;
    /* 0x010 */ s8 unk_010;
    /* 0x011 */ s8 unk_011;
    /* 0x014 */ s32 unk_014;
    /* 0x018 */ s32 unk_018;
    /* 0x01C */ s32 unk_01C;
    /* 0x020 */ s8 unk_020[8][8];
    /* 0x060 */ s8 unk_060[8][8];
    /* 0x0A0 */ s32 unk_0A0;
    /* 0x0A4 */ s32 unk_0A4;
    /* 0x0A8 */ u8 unk_0A8[0x138];
    /* 0x1E0 */ s32 unk_1E0;
    /* 0x1E4 */ s32 *unk_1E4;
    /* 0x1E8 */ s32 unk_1E8;
    /* 0x1EC */ u8 unk_1EC[0x48];
    /* 0x234 */ s32 unk_234;
    /* 0x238 */ u8 unk_238[0x8];
    /* 0x240 */ s32 unk_240;
    /* 0x244 */ u8 unk_244[0x20];
    /* 0x264 */ s32 unk_264[5];
} Seq;

typedef struct {
    /* 0x00 */ s32 col;
    /* 0x04 */ s32 row;
} ZigZag;

extern ZigZag D_80087A98[];

s32 func_8008A34C(s32 arg0, s32 arg1) {
    s32 bits;
    s32 i;
    s32 sp18;

    sp18 = ((Seq *)arg0)->unk_240;
    if (arg0 == 0) {
    }
    if (((Seq *)arg0)->unk_1E8 < 2) {
        func_800887D8(arg0);
    }
    ((Seq *)arg0)->unk_1E4++;
    ((Seq *)arg0)->unk_1E8--;
    ((Seq *)arg0)->unk_234 = *((Seq *)arg0)->unk_1E4 << ((Seq *)arg0)->unk_1E0;
    if (((Seq *)arg0)->unk_1E8 < 2) {
        func_800887D8(arg0);
    }
    ((Seq *)arg0)->unk_1E0 = ((Seq *)arg0)->unk_1E0 + 12;
    if ((((Seq *)arg0)->unk_1E0 & 32) != 0) {
        ((Seq *)arg0)->unk_1E0 = ((Seq *)arg0)->unk_1E0 - 32;
        ((Seq *)arg0)->unk_1E4++;
        ((Seq *)arg0)->unk_1E8--;
        if (((Seq *)arg0)->unk_1E0 != 0) {
            ((Seq *)arg0)->unk_234 = ((Seq *)arg0)->unk_234 | ((u32)*((Seq *)arg0)->unk_1E4 >> (u32)(12 - ((Seq *)arg0)->unk_1E0));
        }
        bits = (u32)(((Seq *)arg0)->unk_234 & 0xFFF00000) >> 20;
        ((Seq *)arg0)->unk_234 = *((Seq *)arg0)->unk_1E4 << ((Seq *)arg0)->unk_1E0;
    } else {
        bits = (u32)(((Seq *)arg0)->unk_234 & 0xFFF00000) >> 20;
        ((Seq *)arg0)->unk_234 = ((Seq *)arg0)->unk_234 << 12;
    }
    ((Seq *)arg0)->unk_000 = bits;
    if (((Seq *)arg0)->unk_1E8 < 2) {
        func_800887D8(arg0);
    }
    ((Seq *)arg0)->unk_1E0 = ((Seq *)arg0)->unk_1E0 + 12;
    if ((((Seq *)arg0)->unk_1E0 & 32) != 0) {
        ((Seq *)arg0)->unk_1E0 = ((Seq *)arg0)->unk_1E0 - 32;
        ((Seq *)arg0)->unk_1E4++;
        ((Seq *)arg0)->unk_1E8--;
        if (((Seq *)arg0)->unk_1E0 != 0) {
            ((Seq *)arg0)->unk_234 = ((Seq *)arg0)->unk_234 | ((u32)*((Seq *)arg0)->unk_1E4 >> (u32)(12 - ((Seq *)arg0)->unk_1E0));
        }
        bits = (u32)(((Seq *)arg0)->unk_234 & 0xFFF00000) >> 20;
        ((Seq *)arg0)->unk_234 = *((Seq *)arg0)->unk_1E4 << ((Seq *)arg0)->unk_1E0;
    } else {
        bits = (u32)(((Seq *)arg0)->unk_234 & 0xFFF00000) >> 20;
        ((Seq *)arg0)->unk_234 = ((Seq *)arg0)->unk_234 << 12;
    }
    ((Seq *)arg0)->unk_004 = bits;
    ((Seq *)arg0)->unk_00C = (u32)(((Seq *)arg0)->unk_000 + 15) >> 4;
    ((Seq *)arg0)->unk_008 = (u32)(((Seq *)arg0)->unk_004 + 15) >> 4;
    if (((Seq *)arg0)->unk_264[0] == 0) {
        for (i = 0; i < 5; i++) {
            ((Seq *)arg0)->unk_264[i] = func_80089984(arg0, arg1);
        }
    }
    if (((Seq *)arg0)->unk_1E8 < 2) {
        func_800887D8(arg0);
    }
    ((Seq *)arg0)->unk_1E0 = ((Seq *)arg0)->unk_1E0 + 4;
    if ((((Seq *)arg0)->unk_1E0 & 32) != 0) {
        ((Seq *)arg0)->unk_1E0 = ((Seq *)arg0)->unk_1E0 - 32;
        ((Seq *)arg0)->unk_1E4++;
        ((Seq *)arg0)->unk_1E8--;
        if (((Seq *)arg0)->unk_1E0 != 0) {
            ((Seq *)arg0)->unk_234 = ((Seq *)arg0)->unk_234 | ((u32)*((Seq *)arg0)->unk_1E4 >> (u32)(4 - ((Seq *)arg0)->unk_1E0));
        }
        bits = (u32)(((Seq *)arg0)->unk_234 & 0xF0000000) >> 28;
        ((Seq *)arg0)->unk_234 = *((Seq *)arg0)->unk_1E4 << ((Seq *)arg0)->unk_1E0;
    } else {
        bits = (u32)(((Seq *)arg0)->unk_234 & 0xF0000000) >> 28;
        ((Seq *)arg0)->unk_234 = ((Seq *)arg0)->unk_234 << 4;
    }
    ((Seq *)arg0)->unk_010 = bits;
    if (((Seq *)arg0)->unk_1E8 < 2) {
        func_800887D8(arg0);
    }
    ((Seq *)arg0)->unk_1E0 = ((Seq *)arg0)->unk_1E0 + 4;
    if ((((Seq *)arg0)->unk_1E0 & 32) != 0) {
        ((Seq *)arg0)->unk_1E0 = ((Seq *)arg0)->unk_1E0 - 32;
        ((Seq *)arg0)->unk_1E4++;
        ((Seq *)arg0)->unk_1E8--;
        if (((Seq *)arg0)->unk_1E0 != 0) {
            ((Seq *)arg0)->unk_234 = ((Seq *)arg0)->unk_234 | ((u32)*((Seq *)arg0)->unk_1E4 >> (u32)(4 - ((Seq *)arg0)->unk_1E0));
        }
        bits = (u32)(((Seq *)arg0)->unk_234 & 0xF0000000) >> 28;
        ((Seq *)arg0)->unk_234 = *((Seq *)arg0)->unk_1E4 << ((Seq *)arg0)->unk_1E0;
    } else {
        bits = (u32)(((Seq *)arg0)->unk_234 & 0xF0000000) >> 28;
        ((Seq *)arg0)->unk_234 = ((Seq *)arg0)->unk_234 << 4;
    }
    ((Seq *)arg0)->unk_011 = bits;
    if (((Seq *)arg0)->unk_1E8 < 2) {
        func_800887D8(arg0);
    }
    ((Seq *)arg0)->unk_1E0 = ((Seq *)arg0)->unk_1E0 + 18;
    if ((((Seq *)arg0)->unk_1E0 & 32) != 0) {
        ((Seq *)arg0)->unk_1E0 = ((Seq *)arg0)->unk_1E0 - 32;
        ((Seq *)arg0)->unk_1E4++;
        ((Seq *)arg0)->unk_1E8--;
        if (((Seq *)arg0)->unk_1E0 != 0) {
            ((Seq *)arg0)->unk_234 = ((Seq *)arg0)->unk_234 | ((u32)*((Seq *)arg0)->unk_1E4 >> (u32)(18 - ((Seq *)arg0)->unk_1E0));
        }
        bits = (u32)(((Seq *)arg0)->unk_234 & -0x4000) >> 14;
        ((Seq *)arg0)->unk_234 = *((Seq *)arg0)->unk_1E4 << ((Seq *)arg0)->unk_1E0;
    } else {
        bits = (u32)(((Seq *)arg0)->unk_234 & -0x4000) >> 14;
        ((Seq *)arg0)->unk_234 = ((Seq *)arg0)->unk_234 << 18;
    }
    ((Seq *)arg0)->unk_014 = bits;
    if (arg0 == 0) {
    }
    if (((Seq *)arg0)->unk_1E8 < 2) {
        func_800887D8(arg0);
    }
    ((Seq *)arg0)->unk_1E0 = ((Seq *)arg0)->unk_1E0 + 1;
    if ((((Seq *)arg0)->unk_1E0 & 32) != 0) {
        ((Seq *)arg0)->unk_1E8--;
        ((Seq *)arg0)->unk_1E0 = ((Seq *)arg0)->unk_1E0 - 32;
        ((Seq *)arg0)->unk_1E4++;
        ((Seq *)arg0)->unk_234 = *((Seq *)arg0)->unk_1E4 << ((Seq *)arg0)->unk_1E0;
    } else {
        ((Seq *)arg0)->unk_234 = ((Seq *)arg0)->unk_234 << 1;
    }
    if (((Seq *)arg0)->unk_1E8 < 2) {
        func_800887D8(arg0);
    }
    ((Seq *)arg0)->unk_1E0 = ((Seq *)arg0)->unk_1E0 + 10;
    if ((((Seq *)arg0)->unk_1E0 & 32) != 0) {
        ((Seq *)arg0)->unk_1E0 = ((Seq *)arg0)->unk_1E0 - 32;
        ((Seq *)arg0)->unk_1E4++;
        ((Seq *)arg0)->unk_1E8--;
        if (((Seq *)arg0)->unk_1E0 != 0) {
            ((Seq *)arg0)->unk_234 = ((Seq *)arg0)->unk_234 | ((u32)*((Seq *)arg0)->unk_1E4 >> (u32)(10 - ((Seq *)arg0)->unk_1E0));
        }
        bits = (u32)(((Seq *)arg0)->unk_234 & 0xFFC00000) >> 22;
        ((Seq *)arg0)->unk_234 = *((Seq *)arg0)->unk_1E4 << ((Seq *)arg0)->unk_1E0;
    } else {
        bits = (u32)(((Seq *)arg0)->unk_234 & 0xFFC00000) >> 22;
        ((Seq *)arg0)->unk_234 = ((Seq *)arg0)->unk_234 << 10;
    }
    ((Seq *)arg0)->unk_018 = bits;
    if (((Seq *)arg0)->unk_1E8 < 2) {
        func_800887D8(arg0);
    }
    bits = (u32)((Seq *)arg0)->unk_234 >> 31;
    ((Seq *)arg0)->unk_234 = ((Seq *)arg0)->unk_234 << 1;
    ((Seq *)arg0)->unk_1E0++;
    if ((((Seq *)arg0)->unk_1E0 & 32) != 0) {
        ((Seq *)arg0)->unk_1E0 = 0;
        ((Seq *)arg0)->unk_1E4++;
        ((Seq *)arg0)->unk_234 = *((Seq *)arg0)->unk_1E4;
        ((Seq *)arg0)->unk_1E8--;
    }
    if (bits != 0) {
        ((Seq *)arg0)->unk_01C = 1;
    } else {
        ((Seq *)arg0)->unk_01C = 0;
    }
    if (((Seq *)arg0)->unk_1E8 < 2) {
        func_800887D8(arg0);
    }
    bits = (u32)((Seq *)arg0)->unk_234 >> 31;
    ((Seq *)arg0)->unk_234 = ((Seq *)arg0)->unk_234 << 1;
    ((Seq *)arg0)->unk_1E0++;
    if ((((Seq *)arg0)->unk_1E0 & 32) != 0) {
        ((Seq *)arg0)->unk_1E0 = 0;
        ((Seq *)arg0)->unk_1E4++;
        ((Seq *)arg0)->unk_234 = *((Seq *)arg0)->unk_1E4;
        ((Seq *)arg0)->unk_1E8--;
    }
    if (bits != 0) {
        for (i = 0; i < 64; i++) {
            if (((Seq *)arg0)->unk_1E8 < 2) {
                func_800887D8(arg0);
            }
            ((Seq *)arg0)->unk_1E0 = ((Seq *)arg0)->unk_1E0 + 8;
            if ((((Seq *)arg0)->unk_1E0 & 32) != 0) {
                ((Seq *)arg0)->unk_1E0 = ((Seq *)arg0)->unk_1E0 - 32;
                ((Seq *)arg0)->unk_1E4++;
                ((Seq *)arg0)->unk_1E8--;
                if (((Seq *)arg0)->unk_1E0 != 0) {
                    ((Seq *)arg0)->unk_234 = ((Seq *)arg0)->unk_234 | ((u32)*((Seq *)arg0)->unk_1E4 >> (u32)(8 - ((Seq *)arg0)->unk_1E0));
                }
                bits = (u32)(((Seq *)arg0)->unk_234 & 0xFF000000) >> 24;
                ((Seq *)arg0)->unk_234 = *((Seq *)arg0)->unk_1E4 << ((Seq *)arg0)->unk_1E0;
            } else {
                bits = (u32)(((Seq *)arg0)->unk_234 & 0xFF000000) >> 24;
                ((Seq *)arg0)->unk_234 = ((Seq *)arg0)->unk_234 << 8;
            }
            ((Seq *)arg0)->unk_020[D_80087A98[i].row][D_80087A98[i].col] = bits;
        }
    }
    if (((Seq *)arg0)->unk_1E8 < 2) {
        func_800887D8(arg0);
    }
    bits = (u32)((Seq *)arg0)->unk_234 >> 31;
    ((Seq *)arg0)->unk_234 = ((Seq *)arg0)->unk_234 << 1;
    ((Seq *)arg0)->unk_1E0++;
    if ((((Seq *)arg0)->unk_1E0 & 32) != 0) {
        ((Seq *)arg0)->unk_1E0 = 0;
        ((Seq *)arg0)->unk_1E4++;
        ((Seq *)arg0)->unk_234 = *((Seq *)arg0)->unk_1E4;
        ((Seq *)arg0)->unk_1E8--;
    }
    if (bits != 0) {
        for (i = 0; i < 64; i++) {
            if (((Seq *)arg0)->unk_1E8 < 2) {
                func_800887D8(arg0);
            }
            ((Seq *)arg0)->unk_1E0 = ((Seq *)arg0)->unk_1E0 + 8;
            if ((((Seq *)arg0)->unk_1E0 & 32) != 0) {
                ((Seq *)arg0)->unk_1E0 = ((Seq *)arg0)->unk_1E0 - 32;
                ((Seq *)arg0)->unk_1E4++;
                ((Seq *)arg0)->unk_1E8--;
                if (((Seq *)arg0)->unk_1E0 != 0) {
                    ((Seq *)arg0)->unk_234 = ((Seq *)arg0)->unk_234 | ((u32)*((Seq *)arg0)->unk_1E4 >> (u32)(8 - ((Seq *)arg0)->unk_1E0));
                }
                bits = (u32)(((Seq *)arg0)->unk_234 & 0xFF000000) >> 24;
                ((Seq *)arg0)->unk_234 = *((Seq *)arg0)->unk_1E4 << ((Seq *)arg0)->unk_1E0;
            } else {
                bits = (u32)(((Seq *)arg0)->unk_234 & 0xFF000000) >> 24;
                ((Seq *)arg0)->unk_234 = ((Seq *)arg0)->unk_234 << 8;
            }
            ((Seq *)arg0)->unk_060[D_80087A98[i].row][D_80087A98[i].col] = bits;
        }
    }
    func_80088C58(arg0);
    if (func_800888C0(32, 437, arg0) != 0) {
        if (arg0 == 0) {
        }
        if (((Seq *)arg0)->unk_1E8 < 2) {
            func_800887D8(arg0);
        }
        ((Seq *)arg0)->unk_1E4++;
        ((Seq *)arg0)->unk_1E8--;
        ((Seq *)arg0)->unk_234 = *((Seq *)arg0)->unk_1E4 << ((Seq *)arg0)->unk_1E0;
        if (((Seq *)arg0)->unk_0A0 != 0) {
            func_800A4C04(((Seq *)arg0)->unk_0A0);
            ((Seq *)arg0)->unk_0A0 = 0;
        }
        ((Seq *)arg0)->unk_0A0 = func_80088A2C(arg0);
    }
    if (func_800888C0(32, 434, arg0) != 0) {
        if (arg0 == 0) {
        }
        if (((Seq *)arg0)->unk_1E8 < 2) {
            func_800887D8(arg0);
        }
        ((Seq *)arg0)->unk_1E4++;
        ((Seq *)arg0)->unk_1E8--;
        ((Seq *)arg0)->unk_234 = *((Seq *)arg0)->unk_1E4 << ((Seq *)arg0)->unk_1E0;
        if (((Seq *)arg0)->unk_0A4 != 0) {
            func_800A4C04(((Seq *)arg0)->unk_0A4);
            ((Seq *)arg0)->unk_0A4 = 0;
        }
        ((Seq *)arg0)->unk_0A4 = func_80088A2C(arg0);
    }
    return 1;
}
