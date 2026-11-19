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
struct gd_D0_s32 { u8 pad[0xD0]; s32 v; };
struct gd_108_s32 { u8 pad[0x108]; s32 v; };
struct gd_224_s32 { u8 pad[0x224]; s32 v; };
struct gd_228_s32 { u8 pad[0x228]; s32 v; };
struct gd_22C_s32 { u8 pad[0x22C]; s32 v; };
struct gd_230_s32 { u8 pad[0x230]; s32 v; };
struct gd_258_s32 { u8 pad[0x258]; s32 v; };
struct gd_25C_s32 { u8 pad[0x25C]; s32 v; };
struct gd_260_s32 { u8 pad[0x260]; s32 v; };
extern s32 D_80086D50;
extern s32 D_800FC098;

void func_8008F828(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 sp0;
    s32 sp4;
    s32 sp8;
    s32 spC;
    s32 sp10;
    s32 sp14;
    s32 sp18;
    s32 sp1C;
    s32 sp20;
    s32 sp24;
    s32 sp28;
    s32 sp2C;
    s32 sp30;
    s32 sp34;
    s32 sp38;
    s32 sp3C;
    s32 sp40;

    sp0 = (u32)((struct gd_108_s32 *)arg0)->v / (u32)((struct gd_C_s32 *)arg0)->v;
    sp4 = (u32)((struct gd_108_s32 *)arg0)->v % (u32)((struct gd_C_s32 *)arg0)->v;
    if (arg1 < 4) {
        ((struct gd_224_s32 *)arg0)->v = arg2 >> 1;
        ((struct gd_228_s32 *)arg0)->v = arg3 >> 1;
        ((struct gd_22C_s32 *)arg0)->v = arg2 & 1;
        ((struct gd_230_s32 *)arg0)->v = arg3 & 1;
        sp18 = *(s32 *)((struct gd_260_s32 *)arg0)->v;
        if (((struct gd_D0_s32 *)arg0)->v == 3) {
            if (((struct gd_258_s32 *)arg0)->v != 0) {
                sp1C = *(s32 *)((struct gd_258_s32 *)arg0)->v;
            }
        } else {
            if (((struct gd_25C_s32 *)arg0)->v != 0) {
                sp1C = *(s32 *)((struct gd_25C_s32 *)arg0)->v;
            }
        }
        sp10 = ((struct gd_C_s32 *)arg0)->v << 4;
        sp8 = sp0 << 4;
        spC = sp4 << 4;
        if (arg1 >= 2) {
            sp8 = sp8 + 8;
        }
        if ((arg1 % 2) != 0) {
            spC = spC + 8;
        }
    } else {
        arg2 = arg2 / 2;
        arg3 = arg3 / 2;
        ((struct gd_224_s32 *)arg0)->v = arg2 >> 1;
        ((struct gd_228_s32 *)arg0)->v = arg3 >> 1;
        ((struct gd_22C_s32 *)arg0)->v = arg2 & 1;
        ((struct gd_230_s32 *)arg0)->v = arg3 & 1;
        sp10 = ((struct gd_C_s32 *)arg0)->v << 3;
        sp8 = sp0 << 3;
        spC = sp4 << 3;
        if (arg1 == 5) {
            sp18 = ((struct gd_4_s32 *)((struct gd_260_s32 *)arg0)->v)->v;
            if (((struct gd_D0_s32 *)arg0)->v == 3) {
                if (((struct gd_258_s32 *)arg0)->v != 0) {
                    sp1C = ((struct gd_4_s32 *)((struct gd_258_s32 *)arg0)->v)->v;
                }
            } else {
                if (((struct gd_25C_s32 *)arg0)->v != 0) {
                    sp1C = ((struct gd_4_s32 *)((struct gd_25C_s32 *)arg0)->v)->v;
                }
            }
        } else {
            sp18 = ((struct gd_8_s32 *)((struct gd_260_s32 *)arg0)->v)->v;
            if (((struct gd_D0_s32 *)arg0)->v == 3) {
                if (((struct gd_258_s32 *)arg0)->v != 0) {
                    sp1C = ((struct gd_8_s32 *)((struct gd_258_s32 *)arg0)->v)->v;
                }
            } else {
                if (((struct gd_25C_s32 *)arg0)->v != 0) {
                    sp1C = ((struct gd_8_s32 *)((struct gd_25C_s32 *)arg0)->v)->v;
                }
            }
        }
    }
    sp30 = ((sp8 * sp10) + sp18) + spC;
    sp20 = ((((sp8 + ((struct gd_228_s32 *)arg0)->v) * sp10) + sp1C) + spC) + ((struct gd_224_s32 *)arg0)->v;
    sp34 = arg0 + 340;
    if ((((struct gd_230_s32 *)arg0)->v == 0) && (((struct gd_22C_s32 *)arg0)->v == 0)) {
        sp38 = (s32)&D_800FC098;
        if (arg4 == 0) {
            sp14 = 0;
            for (;;) {
                if (sp14 >= 4) {
                    break;
                }
                (*(s8 *)sp30) = *(u8 *)(((*(u8 *)sp20) + (*(s16 *)sp34)) + sp38);
                (*(s8 *)(sp30 + 1)) = *(u8 *)(((*(u8 *)(sp20 + 1)) + (*(s16 *)(sp34 + 2))) + sp38);
                (*(s8 *)(sp30 + 2)) = *(u8 *)(((*(u8 *)(sp20 + 2)) + (*(s16 *)(sp34 + 4))) + sp38);
                (*(s8 *)(sp30 + 3)) = *(u8 *)(((*(u8 *)(sp20 + 3)) + (*(s16 *)(sp34 + 6))) + sp38);
                (*(s8 *)(sp30 + 4)) = *(u8 *)(((*(u8 *)(sp20 + 4)) + (*(s16 *)(sp34 + 8))) + sp38);
                (*(s8 *)(sp30 + 5)) = *(u8 *)(((*(u8 *)(sp20 + 5)) + (*(s16 *)(sp34 + 10))) + sp38);
                (*(s8 *)(sp30 + 6)) = *(u8 *)(((*(u8 *)(sp20 + 6)) + (*(s16 *)(sp34 + 12))) + sp38);
                (*(s8 *)(sp30 + 7)) = *(u8 *)(((*(u8 *)(sp20 + 7)) + (*(s16 *)(sp34 + 14))) + sp38);
                sp30 = sp30 + sp10;
                sp20 = sp20 + sp10;
                (*(s8 *)sp30) = *(u8 *)(((*(u8 *)sp20) + (*(s16 *)(sp34 + 16))) + sp38);
                (*(s8 *)(sp30 + 1)) = *(u8 *)(((*(u8 *)(sp20 + 1)) + (*(s16 *)(sp34 + 18))) + sp38);
                (*(s8 *)(sp30 + 2)) = *(u8 *)(((*(u8 *)(sp20 + 2)) + (*(s16 *)(sp34 + 20))) + sp38);
                (*(s8 *)(sp30 + 3)) = *(u8 *)(((*(u8 *)(sp20 + 3)) + (*(s16 *)(sp34 + 22))) + sp38);
                (*(s8 *)(sp30 + 4)) = *(u8 *)(((*(u8 *)(sp20 + 4)) + (*(s16 *)(sp34 + 24))) + sp38);
                (*(s8 *)(sp30 + 5)) = *(u8 *)(((*(u8 *)(sp20 + 5)) + (*(s16 *)(sp34 + 26))) + sp38);
                (*(s8 *)(sp30 + 6)) = *(u8 *)(((*(u8 *)(sp20 + 6)) + (*(s16 *)(sp34 + 28))) + sp38);
                (*(s8 *)(sp30 + 7)) = *(u8 *)(((*(u8 *)(sp20 + 7)) + (*(s16 *)(sp34 + 30))) + sp38);
                sp34 = sp34 + 32;
                sp30 = sp30 + sp10;
                sp20 = sp20 + sp10;
                sp14++;
            }
        } else {
            if ((((struct gd_224_s32 *)arg0)->v & 1) != 0) {
                sp14 = 0;
                for (;;) {
                    if (sp14 >= 4) {
                        break;
                    }
                    (*(s8 *)sp30) = *(u8 *)sp20;
                    (*(s8 *)(sp30 + 1)) = *(u8 *)(sp20 + 1);
                    (*(s8 *)(sp30 + 2)) = *(u8 *)(sp20 + 2);
                    (*(s8 *)(sp30 + 3)) = *(u8 *)(sp20 + 3);
                    (*(s8 *)(sp30 + 4)) = *(u8 *)(sp20 + 4);
                    (*(s8 *)(sp30 + 5)) = *(u8 *)(sp20 + 5);
                    (*(s8 *)(sp30 + 6)) = *(u8 *)(sp20 + 6);
                    (*(s8 *)(sp30 + 7)) = *(u8 *)(sp20 + 7);
                    sp30 = sp30 + sp10;
                    sp20 = sp20 + sp10;
                    (*(s8 *)sp30) = *(u8 *)sp20;
                    (*(s8 *)(sp30 + 1)) = *(u8 *)(sp20 + 1);
                    (*(s8 *)(sp30 + 2)) = *(u8 *)(sp20 + 2);
                    (*(s8 *)(sp30 + 3)) = *(u8 *)(sp20 + 3);
                    (*(s8 *)(sp30 + 4)) = *(u8 *)(sp20 + 4);
                    (*(s8 *)(sp30 + 5)) = *(u8 *)(sp20 + 5);
                    (*(s8 *)(sp30 + 6)) = *(u8 *)(sp20 + 6);
                    (*(s8 *)(sp30 + 7)) = *(u8 *)(sp20 + 7);
                    sp30 = sp30 + sp10;
                    sp20 = sp20 + sp10;
                    sp14++;
                }
            } else {
                if ((((struct gd_224_s32 *)arg0)->v & 2) != 0) {
                    sp3C = sp20;
                    sp40 = sp30;
                    sp10 = sp10 >> 1;
                    sp14 = 0;
                    for (;;) {
                        if (sp14 >= 4) {
                            break;
                        }
                        (*(s16 *)sp40) = *(u16 *)sp3C;
                        (*(s16 *)(sp40 + 2)) = *(u16 *)(sp3C + 2);
                        (*(s16 *)(sp40 + 4)) = *(u16 *)(sp3C + 4);
                        (*(s16 *)(sp40 + 6)) = *(u16 *)(sp3C + 6);
                        sp40 = sp40 + (sp10 * 2);
                        sp3C = sp3C + (sp10 * 2);
                        (*(s16 *)sp40) = *(u16 *)sp3C;
                        (*(s16 *)(sp40 + 2)) = *(u16 *)(sp3C + 2);
                        (*(s16 *)(sp40 + 4)) = *(u16 *)(sp3C + 4);
                        (*(s16 *)(sp40 + 6)) = *(u16 *)(sp3C + 6);
                        sp40 = sp40 + (sp10 * 2);
                        sp3C = sp3C + (sp10 * 2);
                        sp14++;
                    }
                } else {
                    sp40 = sp20;
                    sp3C = sp30;
                    sp10 = sp10 >> 2;
                    sp14 = 0;
                    for (;;) {
                        if (sp14 >= 4) {
                            break;
                        }
                        (*(s32 *)sp3C) = *(s32 *)sp40;
                        (*(s32 *)(sp3C + 4)) = *(s32 *)(sp40 + 4);
                        sp3C = sp3C + (sp10 * 4);
                        sp40 = sp40 + (sp10 * 4);
                        (*(s32 *)sp3C) = *(s32 *)sp40;
                        (*(s32 *)(sp3C + 4)) = *(s32 *)(sp40 + 4);
                        sp3C = sp3C + (sp10 * 4);
                        sp40 = sp40 + (sp10 * 4);
                        sp14++;
                    }
                }
            }
        }
        return;
    }
    sp40 = (s32)&D_800FC098;
    sp24 = (sp20 + ((struct gd_22C_s32 *)arg0)->v) + (((struct gd_230_s32 *)arg0)->v * sp10);
    if ((((struct gd_22C_s32 *)arg0)->v == 0) || ((((struct gd_230_s32 *)arg0)->v == 0) || (D_80086D50 == 0))) {
        if (arg4 == 0) {
            sp14 = 0;
            for (;;) {
                if (sp14 >= 4) {
                    break;
                }
                (*(s8 *)sp30) = *(u8 *)((((((*(u8 *)sp20) + (*(u8 *)sp24)) + 1) >> 1) + (*(s16 *)sp34)) + sp40);
                (*(s8 *)(sp30 + 1)) = *(u8 *)((((((*(u8 *)(sp20 + 1)) + (*(u8 *)(sp24 + 1))) + 1) >> 1) + (*(s16 *)(sp34 + 2))) + sp40);
                (*(s8 *)(sp30 + 2)) = *(u8 *)((((((*(u8 *)(sp20 + 2)) + (*(u8 *)(sp24 + 2))) + 1) >> 1) + (*(s16 *)(sp34 + 4))) + sp40);
                (*(s8 *)(sp30 + 3)) = *(u8 *)((((((*(u8 *)(sp20 + 3)) + (*(u8 *)(sp24 + 3))) + 1) >> 1) + (*(s16 *)(sp34 + 6))) + sp40);
                (*(s8 *)(sp30 + 4)) = *(u8 *)((((((*(u8 *)(sp20 + 4)) + (*(u8 *)(sp24 + 4))) + 1) >> 1) + (*(s16 *)(sp34 + 8))) + sp40);
                (*(s8 *)(sp30 + 5)) = *(u8 *)((((((*(u8 *)(sp20 + 5)) + (*(u8 *)(sp24 + 5))) + 1) >> 1) + (*(s16 *)(sp34 + 10))) + sp40);
                (*(s8 *)(sp30 + 6)) = *(u8 *)((((((*(u8 *)(sp20 + 6)) + (*(u8 *)(sp24 + 6))) + 1) >> 1) + (*(s16 *)(sp34 + 12))) + sp40);
                (*(s8 *)(sp30 + 7)) = *(u8 *)((((((*(u8 *)(sp20 + 7)) + (*(u8 *)(sp24 + 7))) + 1) >> 1) + (*(s16 *)(sp34 + 14))) + sp40);
                sp30 = sp30 + sp10;
                sp20 = sp20 + sp10;
                sp24 = sp24 + sp10;
                (*(s8 *)sp30) = *(u8 *)((((((*(u8 *)sp20) + (*(u8 *)sp24)) + 1) >> 1) + (*(s16 *)(sp34 + 16))) + sp40);
                (*(s8 *)(sp30 + 1)) = *(u8 *)((((((*(u8 *)(sp20 + 1)) + (*(u8 *)(sp24 + 1))) + 1) >> 1) + (*(s16 *)(sp34 + 18))) + sp40);
                (*(s8 *)(sp30 + 2)) = *(u8 *)((((((*(u8 *)(sp20 + 2)) + (*(u8 *)(sp24 + 2))) + 1) >> 1) + (*(s16 *)(sp34 + 20))) + sp40);
                (*(s8 *)(sp30 + 3)) = *(u8 *)((((((*(u8 *)(sp20 + 3)) + (*(u8 *)(sp24 + 3))) + 1) >> 1) + (*(s16 *)(sp34 + 22))) + sp40);
                (*(s8 *)(sp30 + 4)) = *(u8 *)((((((*(u8 *)(sp20 + 4)) + (*(u8 *)(sp24 + 4))) + 1) >> 1) + (*(s16 *)(sp34 + 24))) + sp40);
                (*(s8 *)(sp30 + 5)) = *(u8 *)((((((*(u8 *)(sp20 + 5)) + (*(u8 *)(sp24 + 5))) + 1) >> 1) + (*(s16 *)(sp34 + 26))) + sp40);
                (*(s8 *)(sp30 + 6)) = *(u8 *)((((((*(u8 *)(sp20 + 6)) + (*(u8 *)(sp24 + 6))) + 1) >> 1) + (*(s16 *)(sp34 + 28))) + sp40);
                (*(s8 *)(sp30 + 7)) = *(u8 *)((((((*(u8 *)(sp20 + 7)) + (*(u8 *)(sp24 + 7))) + 1) >> 1) + (*(s16 *)(sp34 + 30))) + sp40);
                sp34 = sp34 + 32;
                sp30 = sp30 + sp10;
                sp20 = sp20 + sp10;
                sp24 = sp24 + sp10;
                sp14++;
            }
        } else {
            sp14 = 0;
            for (;;) {
                if (sp14 >= 8) {
                    break;
                }
                (*(s8 *)sp30) = (((*(u8 *)sp20) + (*(u8 *)sp24)) + 1) >> 1;
                (*(s8 *)(sp30 + 1)) = (((*(u8 *)(sp20 + 1)) + (*(u8 *)(sp24 + 1))) + 1) >> 1;
                (*(s8 *)(sp30 + 2)) = (((*(u8 *)(sp20 + 2)) + (*(u8 *)(sp24 + 2))) + 1) >> 1;
                (*(s8 *)(sp30 + 3)) = (((*(u8 *)(sp20 + 3)) + (*(u8 *)(sp24 + 3))) + 1) >> 1;
                (*(s8 *)(sp30 + 4)) = (((*(u8 *)(sp20 + 4)) + (*(u8 *)(sp24 + 4))) + 1) >> 1;
                (*(s8 *)(sp30 + 5)) = (((*(u8 *)(sp20 + 5)) + (*(u8 *)(sp24 + 5))) + 1) >> 1;
                (*(s8 *)(sp30 + 6)) = (((*(u8 *)(sp20 + 6)) + (*(u8 *)(sp24 + 6))) + 1) >> 1;
                (*(s8 *)(sp30 + 7)) = (((*(u8 *)(sp20 + 7)) + (*(u8 *)(sp24 + 7))) + 1) >> 1;
                sp30 = sp30 + sp10;
                sp20 = sp20 + sp10;
                sp24 = sp24 + sp10;
                sp14++;
            }
        }
        return;
    }
    sp28 = sp20 + ((struct gd_22C_s32 *)arg0)->v;
    sp2C = sp20 + (((struct gd_230_s32 *)arg0)->v * sp10);
    if (arg4 == 0) {
        sp14 = 0;
        for (;;) {
            if (sp14 >= 4) {
                break;
            }
            (*(s8 *)sp30) = *(u8 *)((((((((*(u8 *)sp20) + (*(u8 *)sp24)) + (*(u8 *)sp28)) + (*(u8 *)sp2C)) + 2) >> 2) + (*(s16 *)sp34)) + sp40);
            (*(s8 *)(sp30 + 1)) = *(u8 *)((((((((*(u8 *)(sp20 + 1)) + (*(u8 *)(sp24 + 1))) + (*(u8 *)(sp28 + 1))) + (*(u8 *)(sp2C + 1))) + 2) >> 2) + (*(s16 *)(sp34 + 2))) + sp40);
            (*(s8 *)(sp30 + 2)) = *(u8 *)((((((((*(u8 *)(sp20 + 2)) + (*(u8 *)(sp24 + 2))) + (*(u8 *)(sp28 + 2))) + (*(u8 *)(sp2C + 2))) + 2) >> 2) + (*(s16 *)(sp34 + 4))) + sp40);
            (*(s8 *)(sp30 + 3)) = *(u8 *)((((((((*(u8 *)(sp20 + 3)) + (*(u8 *)(sp24 + 3))) + (*(u8 *)(sp28 + 3))) + (*(u8 *)(sp2C + 3))) + 2) >> 2) + (*(s16 *)(sp34 + 6))) + sp40);
            (*(s8 *)(sp30 + 4)) = *(u8 *)((((((((*(u8 *)(sp20 + 4)) + (*(u8 *)(sp24 + 4))) + (*(u8 *)(sp28 + 4))) + (*(u8 *)(sp2C + 4))) + 2) >> 2) + (*(s16 *)(sp34 + 8))) + sp40);
            (*(s8 *)(sp30 + 5)) = *(u8 *)((((((((*(u8 *)(sp20 + 5)) + (*(u8 *)(sp24 + 5))) + (*(u8 *)(sp28 + 5))) + (*(u8 *)(sp2C + 5))) + 2) >> 2) + (*(s16 *)(sp34 + 10))) + sp40);
            (*(s8 *)(sp30 + 6)) = *(u8 *)((((((((*(u8 *)(sp20 + 6)) + (*(u8 *)(sp24 + 6))) + (*(u8 *)(sp28 + 6))) + (*(u8 *)(sp2C + 6))) + 2) >> 2) + (*(s16 *)(sp34 + 12))) + sp40);
            (*(s8 *)(sp30 + 7)) = *(u8 *)((((((((*(u8 *)(sp20 + 7)) + (*(u8 *)(sp24 + 7))) + (*(u8 *)(sp28 + 7))) + (*(u8 *)(sp2C + 7))) + 2) >> 2) + (*(s16 *)(sp34 + 14))) + sp40);
            sp30 = sp30 + sp10;
            sp20 = sp20 + sp10;
            sp24 = sp24 + sp10;
            sp28 = sp28 + sp10;
            sp2C = sp2C + sp10;
            (*(s8 *)sp30) = *(u8 *)((((((((*(u8 *)sp20) + (*(u8 *)sp24)) + (*(u8 *)sp28)) + (*(u8 *)sp2C)) + 2) >> 2) + (*(s16 *)(sp34 + 16))) + sp40);
            (*(s8 *)(sp30 + 1)) = *(u8 *)((((((((*(u8 *)(sp20 + 1)) + (*(u8 *)(sp24 + 1))) + (*(u8 *)(sp28 + 1))) + (*(u8 *)(sp2C + 1))) + 2) >> 2) + (*(s16 *)(sp34 + 18))) + sp40);
            (*(s8 *)(sp30 + 2)) = *(u8 *)((((((((*(u8 *)(sp20 + 2)) + (*(u8 *)(sp24 + 2))) + (*(u8 *)(sp28 + 2))) + (*(u8 *)(sp2C + 2))) + 2) >> 2) + (*(s16 *)(sp34 + 20))) + sp40);
            (*(s8 *)(sp30 + 3)) = *(u8 *)((((((((*(u8 *)(sp20 + 3)) + (*(u8 *)(sp24 + 3))) + (*(u8 *)(sp28 + 3))) + (*(u8 *)(sp2C + 3))) + 2) >> 2) + (*(s16 *)(sp34 + 22))) + sp40);
            (*(s8 *)(sp30 + 4)) = *(u8 *)((((((((*(u8 *)(sp20 + 4)) + (*(u8 *)(sp24 + 4))) + (*(u8 *)(sp28 + 4))) + (*(u8 *)(sp2C + 4))) + 2) >> 2) + (*(s16 *)(sp34 + 24))) + sp40);
            (*(s8 *)(sp30 + 5)) = *(u8 *)((((((((*(u8 *)(sp20 + 5)) + (*(u8 *)(sp24 + 5))) + (*(u8 *)(sp28 + 5))) + (*(u8 *)(sp2C + 5))) + 2) >> 2) + (*(s16 *)(sp34 + 26))) + sp40);
            (*(s8 *)(sp30 + 6)) = *(u8 *)((((((((*(u8 *)(sp20 + 6)) + (*(u8 *)(sp24 + 6))) + (*(u8 *)(sp28 + 6))) + (*(u8 *)(sp2C + 6))) + 2) >> 2) + (*(s16 *)(sp34 + 28))) + sp40);
            (*(s8 *)(sp30 + 7)) = *(u8 *)((((((((*(u8 *)(sp20 + 7)) + (*(u8 *)(sp24 + 7))) + (*(u8 *)(sp28 + 7))) + (*(u8 *)(sp2C + 7))) + 2) >> 2) + (*(s16 *)(sp34 + 30))) + sp40);
            sp34 = sp34 + 32;
            sp30 = sp30 + sp10;
            sp20 = sp20 + sp10;
            sp24 = sp24 + sp10;
            sp28 = sp28 + sp10;
            sp2C = sp2C + sp10;
            sp14++;
        }
        return;
    }
    sp14 = 0;
    for (;;) {
        if (sp14 >= 8) {
            return;
        }
        (*(s8 *)sp30) = (((((*(u8 *)sp20) + (*(u8 *)sp24)) + (*(u8 *)sp28)) + (*(u8 *)sp2C)) + 2) >> 2;
        (*(s8 *)(sp30 + 1)) = (((((*(u8 *)(sp20 + 1)) + (*(u8 *)(sp24 + 1))) + (*(u8 *)(sp28 + 1))) + (*(u8 *)(sp2C + 1))) + 2) >> 2;
        (*(s8 *)(sp30 + 2)) = (((((*(u8 *)(sp20 + 2)) + (*(u8 *)(sp24 + 2))) + (*(u8 *)(sp28 + 2))) + (*(u8 *)(sp2C + 2))) + 2) >> 2;
        (*(s8 *)(sp30 + 3)) = (((((*(u8 *)(sp20 + 3)) + (*(u8 *)(sp24 + 3))) + (*(u8 *)(sp28 + 3))) + (*(u8 *)(sp2C + 3))) + 2) >> 2;
        (*(s8 *)(sp30 + 4)) = (((((*(u8 *)(sp20 + 4)) + (*(u8 *)(sp24 + 4))) + (*(u8 *)(sp28 + 4))) + (*(u8 *)(sp2C + 4))) + 2) >> 2;
        (*(s8 *)(sp30 + 5)) = (((((*(u8 *)(sp20 + 5)) + (*(u8 *)(sp24 + 5))) + (*(u8 *)(sp28 + 5))) + (*(u8 *)(sp2C + 5))) + 2) >> 2;
        (*(s8 *)(sp30 + 6)) = (((((*(u8 *)(sp20 + 6)) + (*(u8 *)(sp24 + 6))) + (*(u8 *)(sp28 + 6))) + (*(u8 *)(sp2C + 6))) + 2) >> 2;
        (*(s8 *)(sp30 + 7)) = (((((*(u8 *)(sp20 + 7)) + (*(u8 *)(sp24 + 7))) + (*(u8 *)(sp28 + 7))) + (*(u8 *)(sp2C + 7))) + 2) >> 2;
        sp30 = sp30 + sp10;
        sp20 = sp20 + sp10;
        sp24 = sp24 + sp10;
        sp28 = sp28 + sp10;
        sp2C = sp2C + sp10;
        sp14++;
    }
}
