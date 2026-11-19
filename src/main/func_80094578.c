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

struct gd_4_s32 { u8 pad[0x4]; s32 v; };
struct gd_8_s32 { u8 pad[0x8]; s32 v; };
struct gd_C_s32 { u8 pad[0xC]; s32 v; };
struct gd_D8_s32 { u8 pad[0xD8]; s32 v; };
struct gd_E4_s32 { u8 pad[0xE4]; s32 v; };
struct gd_108_s32 { u8 pad[0x108]; s32 v; };
struct gd_10C_s32 { u8 pad[0x10C]; s32 v; };
struct gd_138_s32 { u8 pad[0x138]; s32 v; };
struct gd_13C_s32 { u8 pad[0x13C]; s32 v; };
struct gd_144_s32 { u8 pad[0x144]; s32 v; };
struct gd_148_s32 { u8 pad[0x148]; s32 v; };
struct gd_14C_s32 { u8 pad[0x14C]; s32 v; };
struct gd_150_s32 { u8 pad[0x150]; s32 v; };
struct gd_240_s32 { u8 pad[0x240]; s32 v; };
struct gd_258_s32 { u8 pad[0x258]; s32 v; };
struct gd_25C_s32 { u8 pad[0x25C]; s32 v; };
struct gd_260_s32 { u8 pad[0x260]; s32 v; };
s32 func_80095664();

void func_80094578(s32 arg0) {
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
    s32 sp68;
    s32 sp6C;
    s32 sp70;
    s32 sp74;
    s32 sp78;
    s32 sp7C;
    s32 sp80;
    s32 sp84;
    s32 sp88;
    s32 sp8C;
    s32 sp90;
    s32 sp94;
    s32 sp98[64];
    s32 sp198[16];
    s32 sp1D8[16];
    s32 sp218[64];
    s32 sp318[16];
    s32 sp358[16];
    s32 sp398;
    s32 sp39C;
    s32 sp3A0;
    s32 sp3A4;
    s32 sp3A8;
    s32 sp3AC;
    s32 sp3B0;
    s32 sp3B4;
    s32 sp3B8;
    s32 sp3BC;
    s32 sp3C0;

    sp44 = 0;
    sp48 = 0;
    sp4C = 0;
    sp50 = 0;
    sp54 = 0;
    sp58 = 0;
    sp5C = 0;
    sp60 = 0;
    sp68 = 0;
    sp6C = 0;
    sp80 = 0;
    sp84 = 0;
    sp88 = 0;
    sp8C = 0;
    sp90 = 0;
    sp94 = 0;
    sp3A8 = ((struct gd_240_s32 *)arg0)->v;
    sp28 = ((struct gd_C_s32 *)arg0)->v << 4;
    sp2C = sp28 >> 1;
    sp398 = sp28 >> 2;
    sp39C = sp2C >> 2;
    if (((struct gd_D8_s32 *)arg0)->v != 0) {
        sp70 = ((struct gd_144_s32 *)arg0)->v << 1;
        sp74 = ((struct gd_148_s32 *)arg0)->v << 1;
    } else {
        sp70 = ((struct gd_144_s32 *)arg0)->v;
        sp74 = ((struct gd_148_s32 *)arg0)->v;
    }
    if (((struct gd_E4_s32 *)arg0)->v != 0) {
        sp78 = ((struct gd_14C_s32 *)arg0)->v << 1;
        sp7C = ((struct gd_150_s32 *)arg0)->v << 1;
    } else {
        sp78 = ((struct gd_14C_s32 *)arg0)->v;
        sp7C = ((struct gd_150_s32 *)arg0)->v;
    }
    if (((struct gd_138_s32 *)arg0)->v != 0) {
        sp68 = sp70 >> 1;
        sp6C = sp74 >> 1;
        sp44 = sp70 & 1;
        sp48 = sp74 & 1;
        sp70 = sp70 / 2;
        sp74 = sp74 / 2;
        sp88 = sp70 >> 1;
        sp8C = sp74 >> 1;
        sp4C = sp70 & 1;
        sp50 = sp74 & 1;
    }
    if (((struct gd_13C_s32 *)arg0)->v != 0) {
        sp80 = sp78 >> 1;
        sp84 = sp7C >> 1;
        sp54 = sp78 & 1;
        sp58 = sp7C & 1;
        sp78 = sp78 / 2;
        sp7C = sp7C / 2;
        sp90 = sp78 >> 1;
        sp94 = sp7C >> 1;
        sp5C = sp78 & 1;
        sp60 = sp7C & 1;
    }
    sp64 = ((struct gd_10C_s32 *)arg0)->v + 1;
    for (;;) {
        if (sp64 >= ((struct gd_108_s32 *)arg0)->v) {
            return;
        }
        sp30 = (u32)sp64 / (u32)((struct gd_C_s32 *)arg0)->v;
        sp34 = (u32)sp64 % (u32)((struct gd_C_s32 *)arg0)->v;
        sp38 = sp30 << 4;
        sp3C = sp34 << 4;
        sp3A4 = sp38 / 2;
        sp3A0 = sp3C / 2;
        if (((struct gd_138_s32 *)arg0)->v != 0) {
            func_80095664((*(s32 *)((struct gd_258_s32 *)arg0)->v), ((s32)&sp98), sp38, sp3C, sp28, sp68, sp6C, sp44, sp48, 16);
            func_80095664(((struct gd_4_s32 *)((struct gd_258_s32 *)arg0)->v)->v, ((s32)&sp198), sp3A4, sp3A0, sp2C, sp88, sp8C, sp4C, sp50, 8);
            func_80095664(((struct gd_8_s32 *)((struct gd_258_s32 *)arg0)->v)->v, ((s32)&sp1D8), sp3A4, sp3A0, sp2C, sp88, sp8C, sp4C, sp50, 8);
        }
        if (((struct gd_13C_s32 *)arg0)->v != 0) {
            func_80095664((*(s32 *)((struct gd_25C_s32 *)arg0)->v), ((s32)&sp218), sp38, sp3C, sp28, sp80, sp84, sp54, sp58, 16);
            func_80095664(((struct gd_4_s32 *)((struct gd_25C_s32 *)arg0)->v)->v, ((s32)&sp318), sp3A4, sp3A0, sp2C, sp90, sp94, sp5C, sp60, 8);
            func_80095664(((struct gd_8_s32 *)((struct gd_25C_s32 *)arg0)->v)->v, ((s32)&sp358), sp3A4, sp3A0, sp2C, sp90, sp94, sp5C, sp60, 8);
        }
        if ((((struct gd_138_s32 *)arg0)->v != 0) && (((struct gd_13C_s32 *)arg0)->v == 0)) {
            sp3AC = ((*(s32 *)((struct gd_260_s32 *)arg0)->v) + (sp38 * sp28)) + sp3C;
            sp3B4 = (s32)&sp98;
            sp40 = 0;
            for (;;) {
                if (sp40 >= 16) {
                    break;
                }
                (*(s32 *)sp3AC) = *(s32 *)sp3B4;
                (*(s32 *)(sp3AC + 4)) = *(s32 *)(sp3B4 + 4);
                (*(s32 *)(sp3AC + 8)) = *(s32 *)(sp3B4 + 8);
                (*(s32 *)(sp3AC + 12)) = *(s32 *)(sp3B4 + 12);
                sp3AC = sp3AC + (sp398 * 4);
                sp3B4 = sp3B4 + 16;
                sp40++;
            }
            sp3AC = (((struct gd_4_s32 *)((struct gd_260_s32 *)arg0)->v)->v + (sp3A4 * sp2C)) + sp3A0;
            sp3B0 = (((struct gd_8_s32 *)((struct gd_260_s32 *)arg0)->v)->v + (sp3A4 * sp2C)) + sp3A0;
            sp3B4 = (s32)&sp198;
            sp3B8 = (s32)&sp1D8;
            sp40 = 0;
            for (;;) {
                if (sp40 >= 8) {
                    break;
                }
                (*(s32 *)sp3AC) = *(s32 *)sp3B4;
                (*(s32 *)(sp3AC + 4)) = *(s32 *)(sp3B4 + 4);
                (*(s32 *)sp3B0) = *(s32 *)sp3B8;
                (*(s32 *)(sp3B0 + 4)) = *(s32 *)(sp3B8 + 4);
                sp3AC = sp3AC + (sp39C * 4);
                sp3B0 = sp3B0 + (sp39C * 4);
                sp3B4 = sp3B4 + 8;
                sp3B8 = sp3B8 + 8;
                sp40++;
            }
        } else {
            if ((((struct gd_13C_s32 *)arg0)->v != 0) && (((struct gd_138_s32 *)arg0)->v == 0)) {
                sp3B0 = ((*(s32 *)((struct gd_260_s32 *)arg0)->v) + (sp38 * sp28)) + sp3C;
                sp3B8 = (s32)&sp218;
                sp40 = 0;
                for (;;) {
                    if (sp40 >= 16) {
                        break;
                    }
                    (*(s32 *)sp3B0) = *(s32 *)sp3B8;
                    (*(s32 *)(sp3B0 + 4)) = *(s32 *)(sp3B8 + 4);
                    (*(s32 *)(sp3B0 + 8)) = *(s32 *)(sp3B8 + 8);
                    (*(s32 *)(sp3B0 + 12)) = *(s32 *)(sp3B8 + 12);
                    sp3B0 = sp3B0 + (sp398 * 4);
                    sp3B8 = sp3B8 + 16;
                    sp40++;
                }
                sp3B0 = (((struct gd_4_s32 *)((struct gd_260_s32 *)arg0)->v)->v + (sp3A4 * sp2C)) + sp3A0;
                sp3AC = (((struct gd_8_s32 *)((struct gd_260_s32 *)arg0)->v)->v + (sp3A4 * sp2C)) + sp3A0;
                sp3B8 = (s32)&sp318;
                sp3B4 = (s32)&sp358;
                sp40 = 0;
                for (;;) {
                    if (sp40 >= 8) {
                        break;
                    }
                    (*(s32 *)sp3B0) = *(s32 *)sp3B8;
                    (*(s32 *)(sp3B0 + 4)) = *(s32 *)(sp3B8 + 4);
                    (*(s32 *)sp3AC) = *(s32 *)sp3B4;
                    (*(s32 *)(sp3AC + 4)) = *(s32 *)(sp3B4 + 4);
                    sp3B0 = sp3B0 + (sp39C * 4);
                    sp3AC = sp3AC + (sp39C * 4);
                    sp3B8 = sp3B8 + 8;
                    sp3B4 = sp3B4 + 8;
                    sp40++;
                }
            } else {
                sp3BC = ((*(s32 *)((struct gd_260_s32 *)arg0)->v) + (sp38 * sp28)) + sp3C;
                sp3B8 = (s32)&sp98;
                sp3B4 = (s32)&sp218;
                sp40 = 0;
                for (;;) {
                    if (sp40 >= 16) {
                        break;
                    }
                    (*(s8 *)sp3BC) = ((*(u8 *)sp3B8) + (*(u8 *)sp3B4)) >> 1;
                    (*(s8 *)(sp3BC + 1)) = ((*(u8 *)(sp3B8 + 1)) + (*(u8 *)(sp3B4 + 1))) >> 1;
                    (*(s8 *)(sp3BC + 2)) = ((*(u8 *)(sp3B8 + 2)) + (*(u8 *)(sp3B4 + 2))) >> 1;
                    (*(s8 *)(sp3BC + 3)) = ((*(u8 *)(sp3B8 + 3)) + (*(u8 *)(sp3B4 + 3))) >> 1;
                    (*(s8 *)(sp3BC + 4)) = ((*(u8 *)(sp3B8 + 4)) + (*(u8 *)(sp3B4 + 4))) >> 1;
                    (*(s8 *)(sp3BC + 5)) = ((*(u8 *)(sp3B8 + 5)) + (*(u8 *)(sp3B4 + 5))) >> 1;
                    (*(s8 *)(sp3BC + 6)) = ((*(u8 *)(sp3B8 + 6)) + (*(u8 *)(sp3B4 + 6))) >> 1;
                    (*(s8 *)(sp3BC + 7)) = ((*(u8 *)(sp3B8 + 7)) + (*(u8 *)(sp3B4 + 7))) >> 1;
                    (*(s8 *)(sp3BC + 8)) = ((*(u8 *)(sp3B8 + 8)) + (*(u8 *)(sp3B4 + 8))) >> 1;
                    (*(s8 *)(sp3BC + 9)) = ((*(u8 *)(sp3B8 + 9)) + (*(u8 *)(sp3B4 + 9))) >> 1;
                    (*(s8 *)(sp3BC + 10)) = ((*(u8 *)(sp3B8 + 10)) + (*(u8 *)(sp3B4 + 10))) >> 1;
                    (*(s8 *)(sp3BC + 11)) = ((*(u8 *)(sp3B8 + 11)) + (*(u8 *)(sp3B4 + 11))) >> 1;
                    (*(s8 *)(sp3BC + 12)) = ((*(u8 *)(sp3B8 + 12)) + (*(u8 *)(sp3B4 + 12))) >> 1;
                    (*(s8 *)(sp3BC + 13)) = ((*(u8 *)(sp3B8 + 13)) + (*(u8 *)(sp3B4 + 13))) >> 1;
                    (*(s8 *)(sp3BC + 14)) = ((*(u8 *)(sp3B8 + 14)) + (*(u8 *)(sp3B4 + 14))) >> 1;
                    (*(s8 *)(sp3BC + 15)) = ((*(u8 *)(sp3B8 + 15)) + (*(u8 *)(sp3B4 + 15))) >> 1;
                    sp3BC = sp3BC + sp28;
                    sp3B8 = sp3B8 + 16;
                    sp3B4 = sp3B4 + 16;
                    sp40++;
                }
                sp3BC = (((struct gd_4_s32 *)((struct gd_260_s32 *)arg0)->v)->v + (sp3A4 * sp2C)) + sp3A0;
                sp3C0 = (((struct gd_8_s32 *)((struct gd_260_s32 *)arg0)->v)->v + (sp3A4 * sp2C)) + sp3A0;
                sp3B8 = (s32)&sp198;
                sp3B4 = (s32)&sp318;
                sp3B0 = (s32)&sp1D8;
                sp3AC = (s32)&sp358;
                sp40 = 0;
                for (;;) {
                    if (sp40 >= 8) {
                        break;
                    }
                    (*(s8 *)sp3BC) = ((*(u8 *)sp3B8) + (*(u8 *)sp3B4)) >> 1;
                    (*(s8 *)(sp3BC + 1)) = ((*(u8 *)(sp3B8 + 1)) + (*(u8 *)(sp3B4 + 1))) >> 1;
                    (*(s8 *)(sp3BC + 2)) = ((*(u8 *)(sp3B8 + 2)) + (*(u8 *)(sp3B4 + 2))) >> 1;
                    (*(s8 *)(sp3BC + 3)) = ((*(u8 *)(sp3B8 + 3)) + (*(u8 *)(sp3B4 + 3))) >> 1;
                    (*(s8 *)(sp3BC + 4)) = ((*(u8 *)(sp3B8 + 4)) + (*(u8 *)(sp3B4 + 4))) >> 1;
                    (*(s8 *)(sp3BC + 5)) = ((*(u8 *)(sp3B8 + 5)) + (*(u8 *)(sp3B4 + 5))) >> 1;
                    (*(s8 *)(sp3BC + 6)) = ((*(u8 *)(sp3B8 + 6)) + (*(u8 *)(sp3B4 + 6))) >> 1;
                    (*(s8 *)(sp3BC + 7)) = ((*(u8 *)(sp3B8 + 7)) + (*(u8 *)(sp3B4 + 7))) >> 1;
                    sp3BC = sp3BC + sp2C;
                    sp3B8 = sp3B8 + 8;
                    sp3B4 = sp3B4 + 8;
                    (*(s8 *)sp3C0) = ((*(u8 *)sp3B0) + (*(u8 *)sp3AC)) >> 1;
                    (*(s8 *)(sp3C0 + 1)) = ((*(u8 *)(sp3B0 + 1)) + (*(u8 *)(sp3AC + 1))) >> 1;
                    (*(s8 *)(sp3C0 + 2)) = ((*(u8 *)(sp3B0 + 2)) + (*(u8 *)(sp3AC + 2))) >> 1;
                    (*(s8 *)(sp3C0 + 3)) = ((*(u8 *)(sp3B0 + 3)) + (*(u8 *)(sp3AC + 3))) >> 1;
                    (*(s8 *)(sp3C0 + 4)) = ((*(u8 *)(sp3B0 + 4)) + (*(u8 *)(sp3AC + 4))) >> 1;
                    (*(s8 *)(sp3C0 + 5)) = ((*(u8 *)(sp3B0 + 5)) + (*(u8 *)(sp3AC + 5))) >> 1;
                    (*(s8 *)(sp3C0 + 6)) = ((*(u8 *)(sp3B0 + 6)) + (*(u8 *)(sp3AC + 6))) >> 1;
                    (*(s8 *)(sp3C0 + 7)) = ((*(u8 *)(sp3B0 + 7)) + (*(u8 *)(sp3AC + 7))) >> 1;
                    sp3C0 = sp3C0 + sp2C;
                    sp3B0 = sp3B0 + 8;
                    sp3AC = sp3AC + 8;
                    sp40++;
                }
            }
        }
        sp64++;
    }
}
