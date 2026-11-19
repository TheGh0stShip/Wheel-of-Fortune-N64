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
struct gd_108_s32 { u8 pad[0x108]; s32 v; };
struct gd_10C_s32 { u8 pad[0x10C]; s32 v; };
struct gd_144_s32 { u8 pad[0x144]; s32 v; };
struct gd_148_s32 { u8 pad[0x148]; s32 v; };
struct gd_240_s32 { u8 pad[0x240]; s32 v; };
struct gd_25C_s32 { u8 pad[0x25C]; s32 v; };
struct gd_260_s32 { u8 pad[0x260]; s32 v; };

void func_80094064(s32 arg0) {
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

    sp40 = ((struct gd_240_s32 *)arg0)->v;
    sp0 = ((struct gd_C_s32 *)arg0)->v << 4;
    sp4 = sp0 >> 1;
    sp20 = sp0 >> 2;
    sp24 = sp4 >> 2;
    sp1C = ((struct gd_10C_s32 *)arg0)->v + 1;
    for (;;) {
        if (sp1C >= ((struct gd_108_s32 *)arg0)->v) {
            break;
        }
        sp8 = (u32)sp1C / (u32)((struct gd_C_s32 *)arg0)->v;
        spC = (u32)sp1C % (u32)((struct gd_C_s32 *)arg0)->v;
        sp10 = sp8 << 4;
        sp14 = spC << 4;
        sp30 = ((*(s32 *)((struct gd_260_s32 *)arg0)->v) + (sp10 * sp0)) + sp14;
        sp34 = ((*(s32 *)((struct gd_25C_s32 *)arg0)->v) + (sp10 * sp0)) + sp14;
        sp18 = 0;
        for (;;) {
            if (sp18 >= 8) {
                break;
            }
            (*(s32 *)sp30) = *(s32 *)sp34;
            (*(s32 *)(sp30 + 4)) = *(s32 *)(sp34 + 4);
            (*(s32 *)(sp30 + 8)) = *(s32 *)(sp34 + 8);
            (*(s32 *)(sp30 + 12)) = *(s32 *)(sp34 + 12);
            sp30 = sp30 + (sp20 * 4);
            sp34 = sp34 + (sp20 * 4);
            (*(s32 *)sp30) = *(s32 *)sp34;
            (*(s32 *)(sp30 + 4)) = *(s32 *)(sp34 + 4);
            (*(s32 *)(sp30 + 8)) = *(s32 *)(sp34 + 8);
            (*(s32 *)(sp30 + 12)) = *(s32 *)(sp34 + 12);
            sp30 = sp30 + (sp20 * 4);
            sp34 = sp34 + (sp20 * 4);
            sp18++;
        }
        sp28 = sp10 >> 1;
        sp2C = sp14 >> 1;
        sp30 = (((struct gd_4_s32 *)((struct gd_260_s32 *)arg0)->v)->v + (sp28 * sp4)) + sp2C;
        sp34 = (((struct gd_4_s32 *)((struct gd_25C_s32 *)arg0)->v)->v + (sp28 * sp4)) + sp2C;
        sp38 = (((struct gd_8_s32 *)((struct gd_260_s32 *)arg0)->v)->v + (sp28 * sp4)) + sp2C;
        sp3C = (((struct gd_8_s32 *)((struct gd_25C_s32 *)arg0)->v)->v + (sp28 * sp4)) + sp2C;
        sp18 = 0;
        for (;;) {
            if (sp18 >= 4) {
                break;
            }
            (*(s32 *)sp30) = *(s32 *)sp34;
            (*(s32 *)(sp30 + 4)) = *(s32 *)(sp34 + 4);
            (*(s32 *)sp38) = *(s32 *)sp3C;
            (*(s32 *)(sp38 + 4)) = *(s32 *)(sp3C + 4);
            sp30 = sp30 + (sp24 * 4);
            sp34 = sp34 + (sp24 * 4);
            sp38 = sp38 + (sp24 * 4);
            sp3C = sp3C + (sp24 * 4);
            (*(s32 *)sp30) = *(s32 *)sp34;
            (*(s32 *)(sp30 + 4)) = *(s32 *)(sp34 + 4);
            (*(s32 *)sp38) = *(s32 *)sp3C;
            (*(s32 *)(sp38 + 4)) = *(s32 *)(sp3C + 4);
            sp30 = sp30 + (sp24 * 4);
            sp34 = sp34 + (sp24 * 4);
            sp38 = sp38 + (sp24 * 4);
            sp3C = sp3C + (sp24 * 4);
            sp18++;
        }
        sp1C++;
    }
    ((struct gd_144_s32 *)arg0)->v = 0;
    ((struct gd_148_s32 *)arg0)->v = 0;
}
