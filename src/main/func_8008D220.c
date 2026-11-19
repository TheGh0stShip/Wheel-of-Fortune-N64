#ifndef N64DK_M2C_PRELUDE
#define N64DK_M2C_PRELUDE
typedef signed char s8; typedef unsigned char u8; typedef signed short s16; typedef unsigned short u16;
typedef signed int s32; typedef unsigned int u32; typedef signed long long s64; typedef unsigned long long u64;
typedef float f32; typedef double f64;
typedef s32 M2C_UNK; typedef s8 M2C_UNK8; typedef s16 M2C_UNK16; typedef s32 M2C_UNK32; typedef s64 M2C_UNK64;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(expr))
/* unhandled instructions become calls to an unprototyped function: any argument list compiles */
extern s32 m2c_unhandled();
#define M2C_ERROR m2c_unhandled
#define M2C_TRAP_IF m2c_unhandled
#define M2C_BREAK m2c_unhandled
#define M2C_LWL(expr) (expr)
#define M2C_FIRST3BYTES(expr) (expr)
#define M2C_UNALIGNED32(expr) (expr)
#define MULT_HI(a, b) ((s32)(((s64)(a) * (s64)(b)) >> 32))
#define MULTU_HI(a, b) ((u32)(((u64)(a) * (u64)(b)) >> 32))
#define M2C_CARRY 0
#ifndef NULL
#define NULL ((void *)0)
#endif
#endif

struct gd_8_s32 { u8 pad[0x8]; s32 v; };
struct gd_C_s32 { u8 pad[0xC]; s32 v; };
struct gd_D0_s32 { u8 pad[0xD0]; s32 v; };
struct gd_DC_s32 { u8 pad[0xDC]; s32 v; };
struct gd_E0_s32 { u8 pad[0xE0]; s32 v; };
struct gd_E8_s32 { u8 pad[0xE8]; s32 v; };
struct gd_EC_s32 { u8 pad[0xEC]; s32 v; };
struct gd_100_s32 { u8 pad[0x100]; s32 v; };
struct gd_108_s32 { u8 pad[0x108]; s32 v; };
struct gd_10C_s32 { u8 pad[0x10C]; s32 v; };
struct gd_110_s32 { u8 pad[0x110]; s32 v; };
struct gd_114_s32 { u8 pad[0x114]; s32 v; };
struct gd_118_s32 { u8 pad[0x118]; s32 v; };
struct gd_11C_s32 { u8 pad[0x11C]; s32 v; };
struct gd_120_s32 { u8 pad[0x120]; s32 v; };
struct gd_124_s32 { u8 pad[0x124]; s32 v; };
struct gd_128_s32 { u8 pad[0x128]; s32 v; };
struct gd_12C_s32 { u8 pad[0x12C]; s32 v; };
struct gd_130_s32 { u8 pad[0x130]; s32 v; };
struct gd_134_s32 { u8 pad[0x134]; s32 v; };
struct gd_138_s32 { u8 pad[0x138]; s32 v; };
struct gd_13C_s32 { u8 pad[0x13C]; s32 v; };
struct gd_140_s32 { u8 pad[0x140]; s32 v; };
struct gd_144_s32 { u8 pad[0x144]; s32 v; };
struct gd_148_s32 { u8 pad[0x148]; s32 v; };
struct gd_14C_s32 { u8 pad[0x14C]; s32 v; };
struct gd_150_s32 { u8 pad[0x150]; s32 v; };
struct gd_1E0_s32 { u8 pad[0x1E0]; s32 v; };
struct gd_1E4_s32 { u8 pad[0x1E4]; s32 v; };
struct gd_1E8_s32 { u8 pad[0x1E8]; s32 v; };
struct gd_234_s32 { u8 pad[0x234]; s32 v; };
struct gd_240_s32 { u8 pad[0x240]; s32 v; };
struct n64dk_e4 { u8 b[4]; };
struct n64dk_p1E4_4 { u8 pad[0x1E4]; struct n64dk_e4 *v; };
struct n64dk_a80085320 { s32 m0; s32 m4; };
extern struct n64dk_a80085320 D_80085320[];
struct n64dk_a800FF2F8 { s32 m0; s32 m4; };
extern struct n64dk_a800FF2F8 D_800FF2F8[];
struct n64dk_a80103480 { s32 m0; s32 m4; };
extern struct n64dk_a80103480 D_80103480[];
struct n64dk_a801078A0 { s32 m0; s32 m4; s32 m8; s32 mC; s32 m10; s32 m14; };
extern struct n64dk_a801078A0 D_801078A0[];
struct n64dk_a80107EA0 { s32 m0; s32 m4; s32 m8; s32 mC; s32 m10; s32 m14; };
extern struct n64dk_a80107EA0 D_80107EA0[];
extern s32 D_80085108;
extern s32 D_80085310;
s32 func_800887D8();
s32 func_8008F3AC();
s32 func_8008F828();
s32 func_80091684();
s32 func_800933BC();
s32 func_80094064();
s32 func_80094578();
s32 func_800964D0();
s32 func_800998E0();
s32 func_80099C8C();
s32 func_800A4CBC();

s32 func_8008D220(s32 arg0) {
    s32 sp20;
    s32 sp24;
    s32 sp28;
    s32 sp2C;
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
    sp58 = ((struct gd_240_s32 *)arg0)->v;
    for (;;) {
        if (((struct gd_1E8_s32 *)arg0)->v < 2) {
            func_800887D8(arg0);
        }
        sp60 = ((struct gd_1E0_s32 *)arg0)->v + 11;
        if (sp60 >= 33) {
            sp60 = sp60 - 32;
            sp5C = ((u32)(((struct gd_234_s32 *)arg0)->v & 0xFFE00000) >> 21) | ((u32)(*(s32 *)(((struct gd_1E4_s32 *)arg0)->v + 4)) >> (u32)(32 - sp60));
        } else {
            sp5C = (u32)(((struct gd_234_s32 *)arg0)->v & 0xFFE00000) >> 21;
        }
        if (((struct gd_1E8_s32 *)arg0)->v < 2) {
            func_800887D8(arg0);
        }
        sp64 = ((struct gd_1E0_s32 *)arg0)->v + 11;
        if (sp64 >= 33) {
            sp64 = sp64 - 32;
            sp60 = ((u32)(((struct gd_234_s32 *)arg0)->v & 0xFFE00000) >> 21) | ((u32)(*(s32 *)(((struct gd_1E4_s32 *)arg0)->v + 4)) >> (u32)(32 - sp64));
        } else {
            sp60 = (u32)(((struct gd_234_s32 *)arg0)->v & 0xFFE00000) >> 21;
        }
        sp20 = D_80103480[sp60].m0;
        if (arg0 == 0) {
        }
        if (((struct gd_1E8_s32 *)arg0)->v < 2) {
            func_800887D8(arg0);
        }
        ((struct gd_1E0_s32 *)arg0)->v = ((struct gd_1E0_s32 *)arg0)->v + D_80103480[sp60].m4;
        if ((((struct gd_1E0_s32 *)arg0)->v & 32) != 0) {
            ((struct gd_1E8_s32 *)arg0)->v--;
            ((struct gd_1E0_s32 *)arg0)->v = ((struct gd_1E0_s32 *)arg0)->v - 32;
            ((struct n64dk_p1E4_4 *)arg0)->v++;
            ((struct gd_234_s32 *)arg0)->v = (*(s32 *)((struct gd_1E4_s32 *)arg0)->v) << ((struct gd_1E0_s32 *)arg0)->v;
        } else {
            ((struct gd_234_s32 *)arg0)->v = ((struct gd_234_s32 *)arg0)->v << D_80103480[sp60].m4;
        }
        if (D_80103480[sp5C].m4 == 0) {
            sp20 = 1;
        }
        if (sp20 == 35) {
            ((struct gd_108_s32 *)arg0)->v = ((struct gd_108_s32 *)arg0)->v + 33;
            sp20 = 34;
        }
        if (sp20 != 34) {
            break;
        }
    }
    ((struct gd_108_s32 *)arg0)->v = ((struct gd_108_s32 *)arg0)->v + sp20;
    if ((u32)((struct gd_108_s32 *)arg0)->v > (u32)((((struct gd_8_s32 *)arg0)->v * ((struct gd_C_s32 *)arg0)->v) - 1)) {
        return -1;
    }
    if ((((struct gd_108_s32 *)arg0)->v - ((struct gd_10C_s32 *)arg0)->v) >= 2) {
        if (((struct gd_D0_s32 *)arg0)->v == 2) {
            func_80094064(arg0);
        } else {
            if (((struct gd_D0_s32 *)arg0)->v == 3) {
                func_80094578(arg0);
            }
        }
    }
    ((struct gd_10C_s32 *)arg0)->v = ((struct gd_108_s32 *)arg0)->v;
    switch ((u32)((struct gd_D0_s32 *)arg0)->v) {
    case 1:
        if (((struct gd_1E8_s32 *)arg0)->v < 2) {
            func_800887D8(arg0);
        }
        sp60 = ((struct gd_1E0_s32 *)arg0)->v + 2;
        if (sp60 >= 33) {
            sp60 = sp60 - 32;
            sp64 = ((u32)(((struct gd_234_s32 *)arg0)->v & 0xC0000000) >> 30) | ((u32)(*(s32 *)(((struct gd_1E4_s32 *)arg0)->v + 4)) >> (u32)(32 - sp60));
        } else {
            sp64 = (u32)(((struct gd_234_s32 *)arg0)->v & 0xC0000000) >> 30;
        }
        sp48 = 0;
        sp4C = 0;
        sp50 = 0;
        ((struct gd_134_s32 *)arg0)->v = 1;
        sp44 = *(s32 *)((sp64 * 4) + ((s32)&D_80085310));
        if (sp64 != 0) {
            if (arg0 == 0) {
            }
            if (((struct gd_1E8_s32 *)arg0)->v < 2) {
                func_800887D8(arg0);
            }
            ((struct gd_1E0_s32 *)arg0)->v += sp44 + 1;
            if ((((struct gd_1E0_s32 *)arg0)->v & 32) != 0) {
                ((struct gd_1E8_s32 *)arg0)->v--;
                ((struct gd_1E0_s32 *)arg0)->v = ((struct gd_1E0_s32 *)arg0)->v - 32;
                ((struct n64dk_p1E4_4 *)arg0)->v++;
                ((struct gd_234_s32 *)arg0)->v = (*(s32 *)((struct gd_1E4_s32 *)arg0)->v) << ((struct gd_1E0_s32 *)arg0)->v;
            } else {
                ((struct gd_234_s32 *)arg0)->v = ((struct gd_234_s32 *)arg0)->v << (sp44 + 1);
            }
        }
        break;
    case 2:
        if (((struct gd_1E8_s32 *)arg0)->v < 2) {
            func_800887D8(arg0);
        }
        sp60 = ((struct gd_1E0_s32 *)arg0)->v + 6;
        if (sp60 >= 33) {
            sp60 = sp60 - 32;
            sp64 = ((u32)(((struct gd_234_s32 *)arg0)->v & 0xFC000000) >> 26) | ((u32)(*(s32 *)(((struct gd_1E4_s32 *)arg0)->v + 4)) >> (u32)(32 - sp60));
        } else {
            sp64 = (u32)(((struct gd_234_s32 *)arg0)->v & 0xFC000000) >> 26;
        }
        sp44 = D_80107EA0[sp64].m0;
        sp48 = D_80107EA0[sp64].m4;
        sp4C = D_80107EA0[sp64].m8;
        sp50 = D_80107EA0[sp64].mC;
        ((struct gd_134_s32 *)arg0)->v = D_80107EA0[sp64].m10;
        if (arg0 == 0) {
        }
        if (((struct gd_1E8_s32 *)arg0)->v < 2) {
            func_800887D8(arg0);
        }
        ((struct gd_1E0_s32 *)arg0)->v = ((struct gd_1E0_s32 *)arg0)->v + D_80107EA0[sp64].m14;
        if ((((struct gd_1E0_s32 *)arg0)->v & 32) != 0) {
            ((struct gd_1E8_s32 *)arg0)->v--;
            ((struct gd_1E0_s32 *)arg0)->v = ((struct gd_1E0_s32 *)arg0)->v - 32;
            ((struct n64dk_p1E4_4 *)arg0)->v++;
            ((struct gd_234_s32 *)arg0)->v = (*(s32 *)((struct gd_1E4_s32 *)arg0)->v) << ((struct gd_1E0_s32 *)arg0)->v;
        } else {
            ((struct gd_234_s32 *)arg0)->v = ((struct gd_234_s32 *)arg0)->v << D_80107EA0[sp64].m14;
        }
        break;
    case 3:
        if (((struct gd_1E8_s32 *)arg0)->v < 2) {
            func_800887D8(arg0);
        }
        sp60 = ((struct gd_1E0_s32 *)arg0)->v + 6;
        if (sp60 >= 33) {
            sp60 = sp60 - 32;
            sp64 = ((u32)(((struct gd_234_s32 *)arg0)->v & 0xFC000000) >> 26) | ((u32)(*(s32 *)(((struct gd_1E4_s32 *)arg0)->v + 4)) >> (u32)(32 - sp60));
        } else {
            sp64 = (u32)(((struct gd_234_s32 *)arg0)->v & 0xFC000000) >> 26;
        }
        sp44 = D_801078A0[sp64].m0;
        sp48 = D_801078A0[sp64].m4;
        sp4C = D_801078A0[sp64].m8;
        sp50 = D_801078A0[sp64].mC;
        ((struct gd_134_s32 *)arg0)->v = D_801078A0[sp64].m10;
        if (arg0 == 0) {
        }
        if (((struct gd_1E8_s32 *)arg0)->v < 2) {
            func_800887D8(arg0);
        }
        ((struct gd_1E0_s32 *)arg0)->v = ((struct gd_1E0_s32 *)arg0)->v + D_801078A0[sp64].m14;
        if ((((struct gd_1E0_s32 *)arg0)->v & 32) != 0) {
            ((struct gd_1E8_s32 *)arg0)->v--;
            ((struct gd_1E0_s32 *)arg0)->v = ((struct gd_1E0_s32 *)arg0)->v - 32;
            ((struct n64dk_p1E4_4 *)arg0)->v++;
            ((struct gd_234_s32 *)arg0)->v = (*(s32 *)((struct gd_1E4_s32 *)arg0)->v) << ((struct gd_1E0_s32 *)arg0)->v;
        } else {
            ((struct gd_234_s32 *)arg0)->v = ((struct gd_234_s32 *)arg0)->v << D_801078A0[sp64].m14;
        }
        break;
    case 4:
        func_800A4CBC(1);
    }
    if (sp44 == 1) {
        if (((struct gd_1E8_s32 *)arg0)->v < 2) {
            func_800887D8(arg0);
        }
        ((struct gd_1E0_s32 *)arg0)->v = ((struct gd_1E0_s32 *)arg0)->v + 5;
        if ((((struct gd_1E0_s32 *)arg0)->v & 32) != 0) {
            ((struct gd_1E0_s32 *)arg0)->v = ((struct gd_1E0_s32 *)arg0)->v - 32;
            ((struct n64dk_p1E4_4 *)arg0)->v++;
            ((struct gd_1E8_s32 *)arg0)->v--;
            if (((struct gd_1E0_s32 *)arg0)->v != 0) {
                ((struct gd_234_s32 *)arg0)->v = ((struct gd_234_s32 *)arg0)->v | ((u32)(*(s32 *)((struct gd_1E4_s32 *)arg0)->v) >> (u32)(5 - ((struct gd_1E0_s32 *)arg0)->v));
            }
            sp24 = (u32)(((struct gd_234_s32 *)arg0)->v & 0xF8000000) >> 27;
            ((struct gd_234_s32 *)arg0)->v = (*(s32 *)((struct gd_1E4_s32 *)arg0)->v) << ((struct gd_1E0_s32 *)arg0)->v;
        } else {
            sp24 = (u32)(((struct gd_234_s32 *)arg0)->v & 0xF8000000) >> 27;
            ((struct gd_234_s32 *)arg0)->v = ((struct gd_234_s32 *)arg0)->v << 5;
        }
        ((struct gd_100_s32 *)arg0)->v = sp24;
    }
    if (sp48 == 1) {
        if (((struct gd_1E8_s32 *)arg0)->v < 2) {
            func_800887D8(arg0);
        }
        sp60 = ((struct gd_1E0_s32 *)arg0)->v + 11;
        if (sp60 >= 33) {
            sp60 = sp60 - 32;
            sp64 = ((u32)(((struct gd_234_s32 *)arg0)->v & 0xFFE00000) >> 21) | ((u32)(*(s32 *)(((struct gd_1E4_s32 *)arg0)->v + 4)) >> (u32)(32 - sp60));
        } else {
            sp64 = (u32)(((struct gd_234_s32 *)arg0)->v & 0xFFE00000) >> 21;
        }
        ((struct gd_110_s32 *)arg0)->v = D_800FF2F8[sp64].m0;
        if (arg0 == 0) {
        }
        if (((struct gd_1E8_s32 *)arg0)->v < 2) {
            func_800887D8(arg0);
        }
        ((struct gd_1E0_s32 *)arg0)->v = ((struct gd_1E0_s32 *)arg0)->v + D_800FF2F8[sp64].m4;
        if ((((struct gd_1E0_s32 *)arg0)->v & 32) != 0) {
            ((struct gd_1E8_s32 *)arg0)->v--;
            ((struct gd_1E0_s32 *)arg0)->v = ((struct gd_1E0_s32 *)arg0)->v - 32;
            ((struct n64dk_p1E4_4 *)arg0)->v++;
            ((struct gd_234_s32 *)arg0)->v = (*(s32 *)((struct gd_1E4_s32 *)arg0)->v) << ((struct gd_1E0_s32 *)arg0)->v;
        } else {
            ((struct gd_234_s32 *)arg0)->v = ((struct gd_234_s32 *)arg0)->v << D_800FF2F8[sp64].m4;
        }
        if (((struct gd_E0_s32 *)arg0)->v != 1) {
            if (((struct gd_110_s32 *)arg0)->v != 0) {
                if (((struct gd_1E8_s32 *)arg0)->v < 2) {
                    func_800887D8(arg0);
                }
                ((struct gd_1E0_s32 *)arg0)->v = ((struct gd_1E0_s32 *)arg0)->v + ((struct gd_DC_s32 *)arg0)->v;
                if ((((struct gd_1E0_s32 *)arg0)->v & 32) != 0) {
                    ((struct gd_1E0_s32 *)arg0)->v = ((struct gd_1E0_s32 *)arg0)->v - 32;
                    ((struct n64dk_p1E4_4 *)arg0)->v++;
                    ((struct gd_1E8_s32 *)arg0)->v--;
                    if (((struct gd_1E0_s32 *)arg0)->v != 0) {
                        ((struct gd_234_s32 *)arg0)->v = ((struct gd_234_s32 *)arg0)->v | ((u32)(*(s32 *)((struct gd_1E4_s32 *)arg0)->v) >> (u32)(((struct gd_DC_s32 *)arg0)->v - ((struct gd_1E0_s32 *)arg0)->v));
                    }
                    sp24 = (u32)(((struct gd_234_s32 *)arg0)->v & (*(s32 *)((((struct gd_DC_s32 *)arg0)->v * 4) + ((s32)&D_80085108)))) >> (u32)(32 - ((struct gd_DC_s32 *)arg0)->v);
                    ((struct gd_234_s32 *)arg0)->v = (*(s32 *)((struct gd_1E4_s32 *)arg0)->v) << ((struct gd_1E0_s32 *)arg0)->v;
                } else {
                    sp24 = (u32)(((struct gd_234_s32 *)arg0)->v & (*(s32 *)((((struct gd_DC_s32 *)arg0)->v * 4) + ((s32)&D_80085108)))) >> (u32)(32 - ((struct gd_DC_s32 *)arg0)->v);
                    ((struct gd_234_s32 *)arg0)->v = ((struct gd_234_s32 *)arg0)->v << ((struct gd_DC_s32 *)arg0)->v;
                }
                ((struct gd_114_s32 *)arg0)->v = sp24;
            }
        }
        if (((struct gd_1E8_s32 *)arg0)->v < 2) {
            func_800887D8(arg0);
        }
        sp60 = ((struct gd_1E0_s32 *)arg0)->v + 11;
        if (sp60 >= 33) {
            sp60 = sp60 - 32;
            sp64 = ((u32)(((struct gd_234_s32 *)arg0)->v & 0xFFE00000) >> 21) | ((u32)(*(s32 *)(((struct gd_1E4_s32 *)arg0)->v + 4)) >> (u32)(32 - sp60));
        } else {
            sp64 = (u32)(((struct gd_234_s32 *)arg0)->v & 0xFFE00000) >> 21;
        }
        ((struct gd_118_s32 *)arg0)->v = D_800FF2F8[sp64].m0;
        if (arg0 == 0) {
        }
        if (((struct gd_1E8_s32 *)arg0)->v < 2) {
            func_800887D8(arg0);
        }
        ((struct gd_1E0_s32 *)arg0)->v = ((struct gd_1E0_s32 *)arg0)->v + D_800FF2F8[sp64].m4;
        if ((((struct gd_1E0_s32 *)arg0)->v & 32) != 0) {
            ((struct gd_1E8_s32 *)arg0)->v--;
            ((struct gd_1E0_s32 *)arg0)->v = ((struct gd_1E0_s32 *)arg0)->v - 32;
            ((struct n64dk_p1E4_4 *)arg0)->v++;
            ((struct gd_234_s32 *)arg0)->v = (*(s32 *)((struct gd_1E4_s32 *)arg0)->v) << ((struct gd_1E0_s32 *)arg0)->v;
        } else {
            ((struct gd_234_s32 *)arg0)->v = ((struct gd_234_s32 *)arg0)->v << D_800FF2F8[sp64].m4;
        }
        if (((struct gd_E0_s32 *)arg0)->v != 1) {
            if (((struct gd_118_s32 *)arg0)->v != 0) {
                if (((struct gd_1E8_s32 *)arg0)->v < 2) {
                    func_800887D8(arg0);
                }
                ((struct gd_1E0_s32 *)arg0)->v = ((struct gd_1E0_s32 *)arg0)->v + ((struct gd_DC_s32 *)arg0)->v;
                if ((((struct gd_1E0_s32 *)arg0)->v & 32) != 0) {
                    ((struct gd_1E0_s32 *)arg0)->v = ((struct gd_1E0_s32 *)arg0)->v - 32;
                    ((struct n64dk_p1E4_4 *)arg0)->v++;
                    ((struct gd_1E8_s32 *)arg0)->v--;
                    if (((struct gd_1E0_s32 *)arg0)->v != 0) {
                        ((struct gd_234_s32 *)arg0)->v = ((struct gd_234_s32 *)arg0)->v | ((u32)(*(s32 *)((struct gd_1E4_s32 *)arg0)->v) >> (u32)(((struct gd_DC_s32 *)arg0)->v - ((struct gd_1E0_s32 *)arg0)->v));
                    }
                    sp24 = (u32)(((struct gd_234_s32 *)arg0)->v & (*(s32 *)((((struct gd_DC_s32 *)arg0)->v * 4) + ((s32)&D_80085108)))) >> (u32)(32 - ((struct gd_DC_s32 *)arg0)->v);
                    ((struct gd_234_s32 *)arg0)->v = (*(s32 *)((struct gd_1E4_s32 *)arg0)->v) << ((struct gd_1E0_s32 *)arg0)->v;
                } else {
                    sp24 = (u32)(((struct gd_234_s32 *)arg0)->v & (*(s32 *)((((struct gd_DC_s32 *)arg0)->v * 4) + ((s32)&D_80085108)))) >> (u32)(32 - ((struct gd_DC_s32 *)arg0)->v);
                    ((struct gd_234_s32 *)arg0)->v = ((struct gd_234_s32 *)arg0)->v << ((struct gd_DC_s32 *)arg0)->v;
                }
                ((struct gd_11C_s32 *)arg0)->v = sp24;
            }
        }
    }
    if (sp4C == 1) {
        if (((struct gd_1E8_s32 *)arg0)->v < 2) {
            func_800887D8(arg0);
        }
        sp60 = ((struct gd_1E0_s32 *)arg0)->v + 11;
        if (sp60 >= 33) {
            sp60 = sp60 - 32;
            sp64 = ((u32)(((struct gd_234_s32 *)arg0)->v & 0xFFE00000) >> 21) | ((u32)(*(s32 *)(((struct gd_1E4_s32 *)arg0)->v + 4)) >> (u32)(32 - sp60));
        } else {
            sp64 = (u32)(((struct gd_234_s32 *)arg0)->v & 0xFFE00000) >> 21;
        }
        ((struct gd_120_s32 *)arg0)->v = D_800FF2F8[sp64].m0;
        if (arg0 == 0) {
        }
        if (((struct gd_1E8_s32 *)arg0)->v < 2) {
            func_800887D8(arg0);
        }
        ((struct gd_1E0_s32 *)arg0)->v = ((struct gd_1E0_s32 *)arg0)->v + D_800FF2F8[sp64].m4;
        if ((((struct gd_1E0_s32 *)arg0)->v & 32) != 0) {
            ((struct gd_1E8_s32 *)arg0)->v--;
            ((struct gd_1E0_s32 *)arg0)->v = ((struct gd_1E0_s32 *)arg0)->v - 32;
            ((struct n64dk_p1E4_4 *)arg0)->v++;
            ((struct gd_234_s32 *)arg0)->v = (*(s32 *)((struct gd_1E4_s32 *)arg0)->v) << ((struct gd_1E0_s32 *)arg0)->v;
        } else {
            ((struct gd_234_s32 *)arg0)->v = ((struct gd_234_s32 *)arg0)->v << D_800FF2F8[sp64].m4;
        }
        if (((struct gd_EC_s32 *)arg0)->v != 1) {
            if (((struct gd_120_s32 *)arg0)->v != 0) {
                if (((struct gd_1E8_s32 *)arg0)->v < 2) {
                    func_800887D8(arg0);
                }
                ((struct gd_1E0_s32 *)arg0)->v = ((struct gd_1E0_s32 *)arg0)->v + ((struct gd_E8_s32 *)arg0)->v;
                if ((((struct gd_1E0_s32 *)arg0)->v & 32) != 0) {
                    ((struct gd_1E0_s32 *)arg0)->v = ((struct gd_1E0_s32 *)arg0)->v - 32;
                    ((struct n64dk_p1E4_4 *)arg0)->v++;
                    ((struct gd_1E8_s32 *)arg0)->v--;
                    if (((struct gd_1E0_s32 *)arg0)->v != 0) {
                        ((struct gd_234_s32 *)arg0)->v = ((struct gd_234_s32 *)arg0)->v | ((u32)(*(s32 *)((struct gd_1E4_s32 *)arg0)->v) >> (u32)(((struct gd_E8_s32 *)arg0)->v - ((struct gd_1E0_s32 *)arg0)->v));
                    }
                    sp24 = (u32)(((struct gd_234_s32 *)arg0)->v & (*(s32 *)((((struct gd_E8_s32 *)arg0)->v * 4) + ((s32)&D_80085108)))) >> (u32)(32 - ((struct gd_E8_s32 *)arg0)->v);
                    ((struct gd_234_s32 *)arg0)->v = (*(s32 *)((struct gd_1E4_s32 *)arg0)->v) << ((struct gd_1E0_s32 *)arg0)->v;
                } else {
                    sp24 = (u32)(((struct gd_234_s32 *)arg0)->v & (*(s32 *)((((struct gd_E8_s32 *)arg0)->v * 4) + ((s32)&D_80085108)))) >> (u32)(32 - ((struct gd_E8_s32 *)arg0)->v);
                    ((struct gd_234_s32 *)arg0)->v = ((struct gd_234_s32 *)arg0)->v << ((struct gd_E8_s32 *)arg0)->v;
                }
                ((struct gd_124_s32 *)arg0)->v = sp24;
            }
        }
        if (((struct gd_1E8_s32 *)arg0)->v < 2) {
            func_800887D8(arg0);
        }
        sp60 = ((struct gd_1E0_s32 *)arg0)->v + 11;
        if (sp60 >= 33) {
            sp60 = sp60 - 32;
            sp64 = ((u32)(((struct gd_234_s32 *)arg0)->v & 0xFFE00000) >> 21) | ((u32)(*(s32 *)(((struct gd_1E4_s32 *)arg0)->v + 4)) >> (u32)(32 - sp60));
        } else {
            sp64 = (u32)(((struct gd_234_s32 *)arg0)->v & 0xFFE00000) >> 21;
        }
        ((struct gd_128_s32 *)arg0)->v = D_800FF2F8[sp64].m0;
        if (arg0 == 0) {
        }
        if (((struct gd_1E8_s32 *)arg0)->v < 2) {
            func_800887D8(arg0);
        }
        ((struct gd_1E0_s32 *)arg0)->v = ((struct gd_1E0_s32 *)arg0)->v + D_800FF2F8[sp64].m4;
        if ((((struct gd_1E0_s32 *)arg0)->v & 32) != 0) {
            ((struct gd_1E8_s32 *)arg0)->v--;
            ((struct gd_1E0_s32 *)arg0)->v = ((struct gd_1E0_s32 *)arg0)->v - 32;
            ((struct n64dk_p1E4_4 *)arg0)->v++;
            ((struct gd_234_s32 *)arg0)->v = (*(s32 *)((struct gd_1E4_s32 *)arg0)->v) << ((struct gd_1E0_s32 *)arg0)->v;
        } else {
            ((struct gd_234_s32 *)arg0)->v = ((struct gd_234_s32 *)arg0)->v << D_800FF2F8[sp64].m4;
        }
        if (((struct gd_EC_s32 *)arg0)->v != 1) {
            if (((struct gd_128_s32 *)arg0)->v != 0) {
                if (((struct gd_1E8_s32 *)arg0)->v < 2) {
                    func_800887D8(arg0);
                }
                ((struct gd_1E0_s32 *)arg0)->v = ((struct gd_1E0_s32 *)arg0)->v + ((struct gd_E8_s32 *)arg0)->v;
                if ((((struct gd_1E0_s32 *)arg0)->v & 32) != 0) {
                    ((struct gd_1E0_s32 *)arg0)->v = ((struct gd_1E0_s32 *)arg0)->v - 32;
                    ((struct n64dk_p1E4_4 *)arg0)->v++;
                    ((struct gd_1E8_s32 *)arg0)->v--;
                    if (((struct gd_1E0_s32 *)arg0)->v != 0) {
                        ((struct gd_234_s32 *)arg0)->v = ((struct gd_234_s32 *)arg0)->v | ((u32)(*(s32 *)((struct gd_1E4_s32 *)arg0)->v) >> (u32)(((struct gd_E8_s32 *)arg0)->v - ((struct gd_1E0_s32 *)arg0)->v));
                    }
                    sp24 = (u32)(((struct gd_234_s32 *)arg0)->v & (*(s32 *)((((struct gd_E8_s32 *)arg0)->v * 4) + ((s32)&D_80085108)))) >> (u32)(32 - ((struct gd_E8_s32 *)arg0)->v);
                    ((struct gd_234_s32 *)arg0)->v = (*(s32 *)((struct gd_1E4_s32 *)arg0)->v) << ((struct gd_1E0_s32 *)arg0)->v;
                } else {
                    sp24 = (u32)(((struct gd_234_s32 *)arg0)->v & (*(s32 *)((((struct gd_E8_s32 *)arg0)->v * 4) + ((s32)&D_80085108)))) >> (u32)(32 - ((struct gd_E8_s32 *)arg0)->v);
                    ((struct gd_234_s32 *)arg0)->v = ((struct gd_234_s32 *)arg0)->v << ((struct gd_E8_s32 *)arg0)->v;
                }
                ((struct gd_12C_s32 *)arg0)->v = sp24;
            }
        }
    }
    if (sp50 == 1) {
        if (((struct gd_1E8_s32 *)arg0)->v < 2) {
            func_800887D8(arg0);
        }
        sp60 = ((struct gd_1E0_s32 *)arg0)->v + 9;
        if (sp60 >= 33) {
            sp60 = sp60 - 32;
            sp64 = ((u32)(((struct gd_234_s32 *)arg0)->v & 0xFF800000) >> 23) | ((u32)(*(s32 *)(((struct gd_1E4_s32 *)arg0)->v + 4)) >> (u32)(32 - sp60));
        } else {
            sp64 = (u32)(((struct gd_234_s32 *)arg0)->v & 0xFF800000) >> 23;
        }
        ((struct gd_130_s32 *)arg0)->v = D_80085320[sp64].m0;
        if (arg0 == 0) {
        }
        if (((struct gd_1E8_s32 *)arg0)->v < 2) {
            func_800887D8(arg0);
        }
        ((struct gd_1E0_s32 *)arg0)->v = ((struct gd_1E0_s32 *)arg0)->v + D_80085320[sp64].m4;
        if ((((struct gd_1E0_s32 *)arg0)->v & 32) != 0) {
            ((struct gd_1E8_s32 *)arg0)->v--;
            ((struct gd_1E0_s32 *)arg0)->v = ((struct gd_1E0_s32 *)arg0)->v - 32;
            ((struct n64dk_p1E4_4 *)arg0)->v++;
            ((struct gd_234_s32 *)arg0)->v = (*(s32 *)((struct gd_1E4_s32 *)arg0)->v) << ((struct gd_1E0_s32 *)arg0)->v;
        } else {
            ((struct gd_234_s32 *)arg0)->v = ((struct gd_234_s32 *)arg0)->v << D_80085320[sp64].m4;
        }
    } else {
        ((struct gd_130_s32 *)arg0)->v = 0;
    }
    if (((struct gd_D0_s32 *)arg0)->v == 2) {
        if (sp48 == 0) {
            sp30 = 0;
            sp34 = 0;
            ((struct gd_144_s32 *)arg0)->v = 0;
            ((struct gd_148_s32 *)arg0)->v = 0;
        } else {
            func_800998E0(((s32)&sp30), ((s32)&sp34), arg0);
        }
    }
    if (((struct gd_D0_s32 *)arg0)->v == 3) {
        if (((struct gd_134_s32 *)arg0)->v != 0) {
            ((struct gd_144_s32 *)arg0)->v = 0;
            ((struct gd_148_s32 *)arg0)->v = 0;
            ((struct gd_14C_s32 *)arg0)->v = 0;
            ((struct gd_150_s32 *)arg0)->v = 0;
        } else {
            if (sp48 == 0) {
                sp30 = ((struct gd_144_s32 *)arg0)->v;
                sp34 = ((struct gd_148_s32 *)arg0)->v;
            } else {
                func_800998E0(((s32)&sp30), ((s32)&sp34), arg0);
            }
            if (sp4C == 0) {
                sp38 = ((struct gd_14C_s32 *)arg0)->v;
                sp3C = ((struct gd_150_s32 *)arg0)->v;
            } else {
                func_80099C8C(((s32)&sp38), ((s32)&sp3C), arg0);
            }
            ((struct gd_138_s32 *)arg0)->v = sp48;
            ((struct gd_13C_s32 *)arg0)->v = sp4C;
        }
    }
    sp28 = 32;
    sp2C = 0;
    for (;;) {
        if (sp2C >= 6) {
            break;
        }
        if ((((struct gd_134_s32 *)arg0)->v != 0) || ((((struct gd_130_s32 *)arg0)->v & sp28) != 0)) {
            sp40 = 0;
            func_800964D0(sp2C, arg0);
        } else {
            sp40 = 1;
        }
        if (((struct gd_134_s32 *)arg0)->v != 0) {
            func_8008F3AC(arg0, sp2C);
        } else {
            if ((sp48 != 0) && (sp4C != 0)) {
                func_800933BC(arg0, sp2C, sp30, sp34, sp38, sp3C, sp40);
            } else {
                if ((sp48 != 0) || (((struct gd_D0_s32 *)arg0)->v == 2)) {
                    func_8008F828(arg0, sp2C, sp30, sp34, sp40);
                } else {
                    if (sp4C != 0) {
                        func_80091684(arg0, sp2C, sp38, sp3C, sp40);
                    }
                }
            }
        }
        sp28 = sp28 >> 1;
        sp2C++;
    }
    if (((struct gd_D0_s32 *)arg0)->v == 4) {
        if (arg0 == 0) {
        }
        if (((struct gd_1E8_s32 *)arg0)->v < 2) {
            func_800887D8(arg0);
        }
        ((struct gd_1E0_s32 *)arg0)->v = ((struct gd_1E0_s32 *)arg0)->v + 1;
        if ((((struct gd_1E0_s32 *)arg0)->v & 32) != 0) {
            ((struct gd_1E8_s32 *)arg0)->v--;
            ((struct gd_1E0_s32 *)arg0)->v = ((struct gd_1E0_s32 *)arg0)->v - 32;
            ((struct n64dk_p1E4_4 *)arg0)->v++;
            ((struct gd_234_s32 *)arg0)->v = (*(s32 *)((struct gd_1E4_s32 *)arg0)->v) << ((struct gd_1E0_s32 *)arg0)->v;
        } else {
            ((struct gd_234_s32 *)arg0)->v = ((struct gd_234_s32 *)arg0)->v << 1;
        }
    }
    if (((struct gd_134_s32 *)arg0)->v != 0) {
        ((struct gd_140_s32 *)arg0)->v = ((struct gd_108_s32 *)arg0)->v;
    }
    return 1;
}
