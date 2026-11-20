#include "wof.h"
#include "mpeg/proto.h"
#include "mpeg/util.h"

typedef struct {
    /* 0x000 */ u8 unk_000[0x8];
    /* 0x008 */ s32 unk_08;
    /* 0x00C */ s32 unk_0C;
    /* 0x010 */ u8 unk_010[0xC0];
    /* 0x0D0 */ s32 unk_D0;
    /* 0x0D4 */ u8 unk_0D4[0x8];
    /* 0x0DC */ s32 unk_DC;
    /* 0x0E0 */ s32 unk_E0;
    /* 0x0E4 */ u8 unk_0E4[0x4];
    /* 0x0E8 */ s32 unk_E8;
    /* 0x0EC */ s32 unk_EC;
    /* 0x0F0 */ u8 unk_0F0[0x10];
    /* 0x100 */ s32 unk_100;
    /* 0x104 */ u8 unk_104[0x4];
    /* 0x108 */ s32 unk_108;
    /* 0x10C */ s32 unk_10C;
    /* 0x110 */ s32 unk_110;
    /* 0x114 */ s32 unk_114;
    /* 0x118 */ s32 unk_118;
    /* 0x11C */ s32 unk_11C;
    /* 0x120 */ s32 unk_120;
    /* 0x124 */ s32 unk_124;
    /* 0x128 */ s32 unk_128;
    /* 0x12C */ s32 unk_12C;
    /* 0x130 */ s32 unk_130;
    /* 0x134 */ s32 unk_134;
    /* 0x138 */ s32 unk_138;
    /* 0x13C */ s32 unk_13C;
    /* 0x140 */ s32 unk_140;
    /* 0x144 */ s32 unk_144;
    /* 0x148 */ s32 unk_148;
    /* 0x14C */ s32 unk_14C;
    /* 0x150 */ s32 unk_150;
    /* 0x154 */ u8 unk_154[0x8C];
    /* 0x1E0 */ s32 bitPos;
    /* 0x1E4 */ s32 *ptr;
    /* 0x1E8 */ s32 wordsLeft;
    /* 0x1EC */ u8 unk_1EC[0x48];
    /* 0x234 */ s32 bits;
    /* 0x238 */ u8 unk_238[0x8];
    /* 0x240 */ s32 unk_240;
} Stream;
typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
} Pair;

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
} Code;

extern Pair D_80085320[];
extern Pair D_800FF2F8[];
extern Pair D_80103480[];
extern Code D_801078A0[];
extern Code D_80107EA0[];

s32 func_8008D220(s32 arg0) {
    s32 sp20;
    s32 sp24;
    s32 mask;
    s32 i;
    s32 sp30;
    s32 sp34;
    s32 sp38;
    s32 sp3C;
    s32 sp40;
    s32 sp44;
    s32 sp48;
    s32 sp4C;
    s32 sp50;
    s32 sp54;
    s32 sp58;
    s32 sp5C;
    s32 sp60;
    s32 sp64;

    sp44 = 0;
    sp48 = 0;
    sp4C = 0;
    sp50 = 0;
    sp54 = 0;
    sp58 = ((Stream *)arg0)->unk_240;
    do {
        if (((Stream *)arg0)->wordsLeft < 2) {
            func_800887D8(arg0);
        }
        sp60 = ((Stream *)arg0)->bitPos + 11;
        if (sp60 >= 33) {
            sp60 = sp60 - 32;
            sp5C = ((u32)(((Stream *)arg0)->bits & 0xFFE00000) >> 21) | ((u32)((Stream *)arg0)->ptr[1] >> (u32)(32 - sp60));
        } else {
            sp5C = (u32)(((Stream *)arg0)->bits & 0xFFE00000) >> 21;
        }
        if (((Stream *)arg0)->wordsLeft < 2) {
            func_800887D8(arg0);
        }
        sp64 = ((Stream *)arg0)->bitPos + 11;
        if (sp64 >= 33) {
            sp64 = sp64 - 32;
            sp60 = ((u32)(((Stream *)arg0)->bits & 0xFFE00000) >> 21) | ((u32)((Stream *)arg0)->ptr[1] >> (u32)(32 - sp64));
        } else {
            sp60 = (u32)(((Stream *)arg0)->bits & 0xFFE00000) >> 21;
        }
        sp20 = D_80103480[sp60].unk_00;
        if (arg0 == 0) {
        }
        if (((Stream *)arg0)->wordsLeft < 2) {
            func_800887D8(arg0);
        }
        ((Stream *)arg0)->bitPos = ((Stream *)arg0)->bitPos + D_80103480[sp60].unk_04;
        if (((Stream *)arg0)->bitPos & 32) {
            ((Stream *)arg0)->wordsLeft--;
            ((Stream *)arg0)->bitPos = ((Stream *)arg0)->bitPos - 32;
            ((Stream *)arg0)->ptr++;
            ((Stream *)arg0)->bits = *((Stream *)arg0)->ptr << ((Stream *)arg0)->bitPos;
        } else {
            ((Stream *)arg0)->bits = ((Stream *)arg0)->bits << D_80103480[sp60].unk_04;
        }
        if (D_80103480[sp5C].unk_04 == 0) {
            sp20 = 1;
        }
        if (sp20 == 35) {
            ((Stream *)arg0)->unk_108 = ((Stream *)arg0)->unk_108 + 33;
            sp20 = 34;
        }
    } while (sp20 == 34);
    ((Stream *)arg0)->unk_108 = ((Stream *)arg0)->unk_108 + sp20;
    if ((u32)((Stream *)arg0)->unk_108 > (u32)(((Stream *)arg0)->unk_08 * ((Stream *)arg0)->unk_0C - 1)) {
        return -1;
    }
    if (((Stream *)arg0)->unk_108 - ((Stream *)arg0)->unk_10C >= 2) {
        if (((Stream *)arg0)->unk_D0 == 2) {
            func_80094064(arg0);
        } else if (((Stream *)arg0)->unk_D0 == 3) {
            func_80094578(arg0);
        }
    }
    ((Stream *)arg0)->unk_10C = ((Stream *)arg0)->unk_108;
    switch ((u32)((Stream *)arg0)->unk_D0) {
    case 1:
        if (((Stream *)arg0)->wordsLeft < 2) {
            func_800887D8(arg0);
        }
        sp60 = ((Stream *)arg0)->bitPos + 2;
        if (sp60 >= 33) {
            sp60 = sp60 - 32;
            sp64 = ((u32)(((Stream *)arg0)->bits & 0xC0000000) >> 30) | ((u32)((Stream *)arg0)->ptr[1] >> (u32)(32 - sp60));
        } else {
            sp64 = (u32)(((Stream *)arg0)->bits & 0xC0000000) >> 30;
        }
        sp48 = 0;
        sp4C = 0;
        sp50 = 0;
        ((Stream *)arg0)->unk_134 = 1;
        sp44 = D_80085310[sp64];
        if (sp64 != 0) {
            if (arg0 == 0) {
            }
            if (((Stream *)arg0)->wordsLeft < 2) {
                func_800887D8(arg0);
            }
            ((Stream *)arg0)->bitPos += sp44 + 1;
            if (((Stream *)arg0)->bitPos & 32) {
                ((Stream *)arg0)->wordsLeft--;
                ((Stream *)arg0)->bitPos = ((Stream *)arg0)->bitPos - 32;
                ((Stream *)arg0)->ptr++;
                ((Stream *)arg0)->bits = *((Stream *)arg0)->ptr << ((Stream *)arg0)->bitPos;
            } else {
                ((Stream *)arg0)->bits = ((Stream *)arg0)->bits << (sp44 + 1);
            }
        }
        break;
    case 2:
        if (((Stream *)arg0)->wordsLeft < 2) {
            func_800887D8(arg0);
        }
        sp60 = ((Stream *)arg0)->bitPos + 6;
        if (sp60 >= 33) {
            sp60 = sp60 - 32;
            sp64 = ((u32)(((Stream *)arg0)->bits & 0xFC000000) >> 26) | ((u32)((Stream *)arg0)->ptr[1] >> (u32)(32 - sp60));
        } else {
            sp64 = (u32)(((Stream *)arg0)->bits & 0xFC000000) >> 26;
        }
        sp44 = D_80107EA0[sp64].unk_00;
        sp48 = D_80107EA0[sp64].unk_04;
        sp4C = D_80107EA0[sp64].unk_08;
        sp50 = D_80107EA0[sp64].unk_0C;
        ((Stream *)arg0)->unk_134 = D_80107EA0[sp64].unk_10;
        if (arg0 == 0) {
        }
        if (((Stream *)arg0)->wordsLeft < 2) {
            func_800887D8(arg0);
        }
        ((Stream *)arg0)->bitPos = ((Stream *)arg0)->bitPos + D_80107EA0[sp64].unk_14;
        if (((Stream *)arg0)->bitPos & 32) {
            ((Stream *)arg0)->wordsLeft--;
            ((Stream *)arg0)->bitPos = ((Stream *)arg0)->bitPos - 32;
            ((Stream *)arg0)->ptr++;
            ((Stream *)arg0)->bits = *((Stream *)arg0)->ptr << ((Stream *)arg0)->bitPos;
        } else {
            ((Stream *)arg0)->bits = ((Stream *)arg0)->bits << D_80107EA0[sp64].unk_14;
        }
        break;
    case 3:
        if (((Stream *)arg0)->wordsLeft < 2) {
            func_800887D8(arg0);
        }
        sp60 = ((Stream *)arg0)->bitPos + 6;
        if (sp60 >= 33) {
            sp60 = sp60 - 32;
            sp64 = ((u32)(((Stream *)arg0)->bits & 0xFC000000) >> 26) | ((u32)((Stream *)arg0)->ptr[1] >> (u32)(32 - sp60));
        } else {
            sp64 = (u32)(((Stream *)arg0)->bits & 0xFC000000) >> 26;
        }
        sp44 = D_801078A0[sp64].unk_00;
        sp48 = D_801078A0[sp64].unk_04;
        sp4C = D_801078A0[sp64].unk_08;
        sp50 = D_801078A0[sp64].unk_0C;
        ((Stream *)arg0)->unk_134 = D_801078A0[sp64].unk_10;
        if (arg0 == 0) {
        }
        if (((Stream *)arg0)->wordsLeft < 2) {
            func_800887D8(arg0);
        }
        ((Stream *)arg0)->bitPos = ((Stream *)arg0)->bitPos + D_801078A0[sp64].unk_14;
        if (((Stream *)arg0)->bitPos & 32) {
            ((Stream *)arg0)->wordsLeft--;
            ((Stream *)arg0)->bitPos = ((Stream *)arg0)->bitPos - 32;
            ((Stream *)arg0)->ptr++;
            ((Stream *)arg0)->bits = *((Stream *)arg0)->ptr << ((Stream *)arg0)->bitPos;
        } else {
            ((Stream *)arg0)->bits = ((Stream *)arg0)->bits << D_801078A0[sp64].unk_14;
        }
        break;
    case 4:
        func_800A4CBC(1);
    }
    if (sp44 == 1) {
        if (((Stream *)arg0)->wordsLeft < 2) {
            func_800887D8(arg0);
        }
        ((Stream *)arg0)->bitPos = ((Stream *)arg0)->bitPos + 5;
        if (((Stream *)arg0)->bitPos & 32) {
            ((Stream *)arg0)->bitPos = ((Stream *)arg0)->bitPos - 32;
            ((Stream *)arg0)->ptr++;
            ((Stream *)arg0)->wordsLeft--;
            if (((Stream *)arg0)->bitPos != 0) {
                ((Stream *)arg0)->bits = ((Stream *)arg0)->bits | ((u32)*((Stream *)arg0)->ptr >> (u32)(5 - ((Stream *)arg0)->bitPos));
            }
            sp24 = (u32)(((Stream *)arg0)->bits & 0xF8000000) >> 27;
            ((Stream *)arg0)->bits = *((Stream *)arg0)->ptr << ((Stream *)arg0)->bitPos;
        } else {
            sp24 = (u32)(((Stream *)arg0)->bits & 0xF8000000) >> 27;
            ((Stream *)arg0)->bits = ((Stream *)arg0)->bits << 5;
        }
        ((Stream *)arg0)->unk_100 = sp24;
    }
    if (sp48 == 1) {
        if (((Stream *)arg0)->wordsLeft < 2) {
            func_800887D8(arg0);
        }
        sp60 = ((Stream *)arg0)->bitPos + 11;
        if (sp60 >= 33) {
            sp60 = sp60 - 32;
            sp64 = ((u32)(((Stream *)arg0)->bits & 0xFFE00000) >> 21) | ((u32)((Stream *)arg0)->ptr[1] >> (u32)(32 - sp60));
        } else {
            sp64 = (u32)(((Stream *)arg0)->bits & 0xFFE00000) >> 21;
        }
        ((Stream *)arg0)->unk_110 = D_800FF2F8[sp64].unk_00;
        if (arg0 == 0) {
        }
        if (((Stream *)arg0)->wordsLeft < 2) {
            func_800887D8(arg0);
        }
        ((Stream *)arg0)->bitPos = ((Stream *)arg0)->bitPos + D_800FF2F8[sp64].unk_04;
        if (((Stream *)arg0)->bitPos & 32) {
            ((Stream *)arg0)->wordsLeft--;
            ((Stream *)arg0)->bitPos = ((Stream *)arg0)->bitPos - 32;
            ((Stream *)arg0)->ptr++;
            ((Stream *)arg0)->bits = *((Stream *)arg0)->ptr << ((Stream *)arg0)->bitPos;
        } else {
            ((Stream *)arg0)->bits = ((Stream *)arg0)->bits << D_800FF2F8[sp64].unk_04;
        }
        if (((Stream *)arg0)->unk_E0 != 1) {
            if (((Stream *)arg0)->unk_110 != 0) {
                if (((Stream *)arg0)->wordsLeft < 2) {
                    func_800887D8(arg0);
                }
                ((Stream *)arg0)->bitPos = ((Stream *)arg0)->bitPos + ((Stream *)arg0)->unk_DC;
                if (((Stream *)arg0)->bitPos & 32) {
                    ((Stream *)arg0)->bitPos = ((Stream *)arg0)->bitPos - 32;
                    ((Stream *)arg0)->ptr++;
                    ((Stream *)arg0)->wordsLeft--;
                    if (((Stream *)arg0)->bitPos != 0) {
                        ((Stream *)arg0)->bits = ((Stream *)arg0)->bits | ((u32)*((Stream *)arg0)->ptr >> (u32)(((Stream *)arg0)->unk_DC - ((Stream *)arg0)->bitPos));
                    }
                    sp24 = (u32)(((Stream *)arg0)->bits & (*(s32 *)((((Stream *)arg0)->unk_DC * 4) + (s32)&D_80085108))) >> (u32)(32 - ((Stream *)arg0)->unk_DC);
                    ((Stream *)arg0)->bits = *((Stream *)arg0)->ptr << ((Stream *)arg0)->bitPos;
                } else {
                    sp24 = (u32)(((Stream *)arg0)->bits & (*(s32 *)((((Stream *)arg0)->unk_DC * 4) + (s32)&D_80085108))) >> (u32)(32 - ((Stream *)arg0)->unk_DC);
                    ((Stream *)arg0)->bits = ((Stream *)arg0)->bits << ((Stream *)arg0)->unk_DC;
                }
                ((Stream *)arg0)->unk_114 = sp24;
            }
        }
        if (((Stream *)arg0)->wordsLeft < 2) {
            func_800887D8(arg0);
        }
        sp60 = ((Stream *)arg0)->bitPos + 11;
        if (sp60 >= 33) {
            sp60 = sp60 - 32;
            sp64 = ((u32)(((Stream *)arg0)->bits & 0xFFE00000) >> 21) | ((u32)((Stream *)arg0)->ptr[1] >> (u32)(32 - sp60));
        } else {
            sp64 = (u32)(((Stream *)arg0)->bits & 0xFFE00000) >> 21;
        }
        ((Stream *)arg0)->unk_118 = D_800FF2F8[sp64].unk_00;
        if (arg0 == 0) {
        }
        if (((Stream *)arg0)->wordsLeft < 2) {
            func_800887D8(arg0);
        }
        ((Stream *)arg0)->bitPos = ((Stream *)arg0)->bitPos + D_800FF2F8[sp64].unk_04;
        if (((Stream *)arg0)->bitPos & 32) {
            ((Stream *)arg0)->wordsLeft--;
            ((Stream *)arg0)->bitPos = ((Stream *)arg0)->bitPos - 32;
            ((Stream *)arg0)->ptr++;
            ((Stream *)arg0)->bits = *((Stream *)arg0)->ptr << ((Stream *)arg0)->bitPos;
        } else {
            ((Stream *)arg0)->bits = ((Stream *)arg0)->bits << D_800FF2F8[sp64].unk_04;
        }
        if (((Stream *)arg0)->unk_E0 != 1) {
            if (((Stream *)arg0)->unk_118 != 0) {
                if (((Stream *)arg0)->wordsLeft < 2) {
                    func_800887D8(arg0);
                }
                ((Stream *)arg0)->bitPos = ((Stream *)arg0)->bitPos + ((Stream *)arg0)->unk_DC;
                if (((Stream *)arg0)->bitPos & 32) {
                    ((Stream *)arg0)->bitPos = ((Stream *)arg0)->bitPos - 32;
                    ((Stream *)arg0)->ptr++;
                    ((Stream *)arg0)->wordsLeft--;
                    if (((Stream *)arg0)->bitPos != 0) {
                        ((Stream *)arg0)->bits = ((Stream *)arg0)->bits | ((u32)*((Stream *)arg0)->ptr >> (u32)(((Stream *)arg0)->unk_DC - ((Stream *)arg0)->bitPos));
                    }
                    sp24 = (u32)(((Stream *)arg0)->bits & (*(s32 *)((((Stream *)arg0)->unk_DC * 4) + (s32)&D_80085108))) >> (u32)(32 - ((Stream *)arg0)->unk_DC);
                    ((Stream *)arg0)->bits = *((Stream *)arg0)->ptr << ((Stream *)arg0)->bitPos;
                } else {
                    sp24 = (u32)(((Stream *)arg0)->bits & (*(s32 *)((((Stream *)arg0)->unk_DC * 4) + (s32)&D_80085108))) >> (u32)(32 - ((Stream *)arg0)->unk_DC);
                    ((Stream *)arg0)->bits = ((Stream *)arg0)->bits << ((Stream *)arg0)->unk_DC;
                }
                ((Stream *)arg0)->unk_11C = sp24;
            }
        }
    }
    if (sp4C == 1) {
        if (((Stream *)arg0)->wordsLeft < 2) {
            func_800887D8(arg0);
        }
        sp60 = ((Stream *)arg0)->bitPos + 11;
        if (sp60 >= 33) {
            sp60 = sp60 - 32;
            sp64 = ((u32)(((Stream *)arg0)->bits & 0xFFE00000) >> 21) | ((u32)((Stream *)arg0)->ptr[1] >> (u32)(32 - sp60));
        } else {
            sp64 = (u32)(((Stream *)arg0)->bits & 0xFFE00000) >> 21;
        }
        ((Stream *)arg0)->unk_120 = D_800FF2F8[sp64].unk_00;
        if (arg0 == 0) {
        }
        if (((Stream *)arg0)->wordsLeft < 2) {
            func_800887D8(arg0);
        }
        ((Stream *)arg0)->bitPos = ((Stream *)arg0)->bitPos + D_800FF2F8[sp64].unk_04;
        if (((Stream *)arg0)->bitPos & 32) {
            ((Stream *)arg0)->wordsLeft--;
            ((Stream *)arg0)->bitPos = ((Stream *)arg0)->bitPos - 32;
            ((Stream *)arg0)->ptr++;
            ((Stream *)arg0)->bits = *((Stream *)arg0)->ptr << ((Stream *)arg0)->bitPos;
        } else {
            ((Stream *)arg0)->bits = ((Stream *)arg0)->bits << D_800FF2F8[sp64].unk_04;
        }
        if (((Stream *)arg0)->unk_EC != 1) {
            if (((Stream *)arg0)->unk_120 != 0) {
                if (((Stream *)arg0)->wordsLeft < 2) {
                    func_800887D8(arg0);
                }
                ((Stream *)arg0)->bitPos = ((Stream *)arg0)->bitPos + ((Stream *)arg0)->unk_E8;
                if (((Stream *)arg0)->bitPos & 32) {
                    ((Stream *)arg0)->bitPos = ((Stream *)arg0)->bitPos - 32;
                    ((Stream *)arg0)->ptr++;
                    ((Stream *)arg0)->wordsLeft--;
                    if (((Stream *)arg0)->bitPos != 0) {
                        ((Stream *)arg0)->bits = ((Stream *)arg0)->bits | ((u32)*((Stream *)arg0)->ptr >> (u32)(((Stream *)arg0)->unk_E8 - ((Stream *)arg0)->bitPos));
                    }
                    sp24 = (u32)(((Stream *)arg0)->bits & (*(s32 *)((((Stream *)arg0)->unk_E8 * 4) + (s32)&D_80085108))) >> (u32)(32 - ((Stream *)arg0)->unk_E8);
                    ((Stream *)arg0)->bits = *((Stream *)arg0)->ptr << ((Stream *)arg0)->bitPos;
                } else {
                    sp24 = (u32)(((Stream *)arg0)->bits & (*(s32 *)((((Stream *)arg0)->unk_E8 * 4) + (s32)&D_80085108))) >> (u32)(32 - ((Stream *)arg0)->unk_E8);
                    ((Stream *)arg0)->bits = ((Stream *)arg0)->bits << ((Stream *)arg0)->unk_E8;
                }
                ((Stream *)arg0)->unk_124 = sp24;
            }
        }
        if (((Stream *)arg0)->wordsLeft < 2) {
            func_800887D8(arg0);
        }
        sp60 = ((Stream *)arg0)->bitPos + 11;
        if (sp60 >= 33) {
            sp60 = sp60 - 32;
            sp64 = ((u32)(((Stream *)arg0)->bits & 0xFFE00000) >> 21) | ((u32)((Stream *)arg0)->ptr[1] >> (u32)(32 - sp60));
        } else {
            sp64 = (u32)(((Stream *)arg0)->bits & 0xFFE00000) >> 21;
        }
        ((Stream *)arg0)->unk_128 = D_800FF2F8[sp64].unk_00;
        if (arg0 == 0) {
        }
        if (((Stream *)arg0)->wordsLeft < 2) {
            func_800887D8(arg0);
        }
        ((Stream *)arg0)->bitPos = ((Stream *)arg0)->bitPos + D_800FF2F8[sp64].unk_04;
        if (((Stream *)arg0)->bitPos & 32) {
            ((Stream *)arg0)->wordsLeft--;
            ((Stream *)arg0)->bitPos = ((Stream *)arg0)->bitPos - 32;
            ((Stream *)arg0)->ptr++;
            ((Stream *)arg0)->bits = *((Stream *)arg0)->ptr << ((Stream *)arg0)->bitPos;
        } else {
            ((Stream *)arg0)->bits = ((Stream *)arg0)->bits << D_800FF2F8[sp64].unk_04;
        }
        if (((Stream *)arg0)->unk_EC != 1) {
            if (((Stream *)arg0)->unk_128 != 0) {
                if (((Stream *)arg0)->wordsLeft < 2) {
                    func_800887D8(arg0);
                }
                ((Stream *)arg0)->bitPos = ((Stream *)arg0)->bitPos + ((Stream *)arg0)->unk_E8;
                if (((Stream *)arg0)->bitPos & 32) {
                    ((Stream *)arg0)->bitPos = ((Stream *)arg0)->bitPos - 32;
                    ((Stream *)arg0)->ptr++;
                    ((Stream *)arg0)->wordsLeft--;
                    if (((Stream *)arg0)->bitPos != 0) {
                        ((Stream *)arg0)->bits = ((Stream *)arg0)->bits | ((u32)*((Stream *)arg0)->ptr >> (u32)(((Stream *)arg0)->unk_E8 - ((Stream *)arg0)->bitPos));
                    }
                    sp24 = (u32)(((Stream *)arg0)->bits & (*(s32 *)((((Stream *)arg0)->unk_E8 * 4) + (s32)&D_80085108))) >> (u32)(32 - ((Stream *)arg0)->unk_E8);
                    ((Stream *)arg0)->bits = *((Stream *)arg0)->ptr << ((Stream *)arg0)->bitPos;
                } else {
                    sp24 = (u32)(((Stream *)arg0)->bits & (*(s32 *)((((Stream *)arg0)->unk_E8 * 4) + (s32)&D_80085108))) >> (u32)(32 - ((Stream *)arg0)->unk_E8);
                    ((Stream *)arg0)->bits = ((Stream *)arg0)->bits << ((Stream *)arg0)->unk_E8;
                }
                ((Stream *)arg0)->unk_12C = sp24;
            }
        }
    }
    if (sp50 == 1) {
        if (((Stream *)arg0)->wordsLeft < 2) {
            func_800887D8(arg0);
        }
        sp60 = ((Stream *)arg0)->bitPos + 9;
        if (sp60 >= 33) {
            sp60 = sp60 - 32;
            sp64 = ((u32)(((Stream *)arg0)->bits & 0xFF800000) >> 23) | ((u32)((Stream *)arg0)->ptr[1] >> (u32)(32 - sp60));
        } else {
            sp64 = (u32)(((Stream *)arg0)->bits & 0xFF800000) >> 23;
        }
        ((Stream *)arg0)->unk_130 = D_80085320[sp64].unk_00;
        if (arg0 == 0) {
        }
        if (((Stream *)arg0)->wordsLeft < 2) {
            func_800887D8(arg0);
        }
        ((Stream *)arg0)->bitPos = ((Stream *)arg0)->bitPos + D_80085320[sp64].unk_04;
        if (((Stream *)arg0)->bitPos & 32) {
            ((Stream *)arg0)->wordsLeft--;
            ((Stream *)arg0)->bitPos = ((Stream *)arg0)->bitPos - 32;
            ((Stream *)arg0)->ptr++;
            ((Stream *)arg0)->bits = *((Stream *)arg0)->ptr << ((Stream *)arg0)->bitPos;
        } else {
            ((Stream *)arg0)->bits = ((Stream *)arg0)->bits << D_80085320[sp64].unk_04;
        }
    } else {
        ((Stream *)arg0)->unk_130 = 0;
    }
    if (((Stream *)arg0)->unk_D0 == 2) {
        if (sp48 == 0) {
            sp30 = 0;
            sp34 = 0;
            ((Stream *)arg0)->unk_144 = 0;
            ((Stream *)arg0)->unk_148 = 0;
        } else {
            func_800998E0((s32)&sp30, (s32)&sp34, arg0);
        }
    }
    if (((Stream *)arg0)->unk_D0 == 3) {
        if (((Stream *)arg0)->unk_134 != 0) {
            ((Stream *)arg0)->unk_144 = 0;
            ((Stream *)arg0)->unk_148 = 0;
            ((Stream *)arg0)->unk_14C = 0;
            ((Stream *)arg0)->unk_150 = 0;
        } else {
            if (sp48 == 0) {
                sp30 = ((Stream *)arg0)->unk_144;
                sp34 = ((Stream *)arg0)->unk_148;
            } else {
                func_800998E0((s32)&sp30, (s32)&sp34, arg0);
            }
            if (sp4C == 0) {
                sp38 = ((Stream *)arg0)->unk_14C;
                sp3C = ((Stream *)arg0)->unk_150;
            } else {
                func_80099C8C((s32)&sp38, (s32)&sp3C, arg0);
            }
            ((Stream *)arg0)->unk_138 = sp48;
            ((Stream *)arg0)->unk_13C = sp4C;
        }
    }
    mask = 32;
    for (i = 0; i < 6; i++) {
        if (((Stream *)arg0)->unk_134 != 0 || (((Stream *)arg0)->unk_130 & mask) != 0) {
            sp40 = 0;
            func_800964D0(i, arg0);
        } else {
            sp40 = 1;
        }
        if (((Stream *)arg0)->unk_134 != 0) {
            func_8008F3AC(arg0, i);
        } else if (sp48 != 0 && sp4C != 0) {
            func_800933BC(arg0, i, sp30, sp34, sp38, sp3C, sp40);
        } else if (sp48 != 0 || ((Stream *)arg0)->unk_D0 == 2) {
            func_8008F828(arg0, i, sp30, sp34, sp40);
        } else if (sp4C != 0) {
            func_80091684(arg0, i, sp38, sp3C, sp40);
        }
        mask = mask >> 1;
    }
    if (((Stream *)arg0)->unk_D0 == 4) {
        if (arg0 == 0) {
        }
        if (((Stream *)arg0)->wordsLeft < 2) {
            func_800887D8(arg0);
        }
        ((Stream *)arg0)->bitPos = ((Stream *)arg0)->bitPos + 1;
        if (((Stream *)arg0)->bitPos & 32) {
            ((Stream *)arg0)->wordsLeft--;
            ((Stream *)arg0)->bitPos = ((Stream *)arg0)->bitPos - 32;
            ((Stream *)arg0)->ptr++;
            ((Stream *)arg0)->bits = *((Stream *)arg0)->ptr << ((Stream *)arg0)->bitPos;
        } else {
            ((Stream *)arg0)->bits = ((Stream *)arg0)->bits << 1;
        }
    }
    if (((Stream *)arg0)->unk_134 != 0) {
        ((Stream *)arg0)->unk_140 = ((Stream *)arg0)->unk_108;
    }
    return 1;
}
