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

struct gd_18_s32 { u8 pad[0x18]; s32 v; };
struct gd_1C_s32 { u8 pad[0x1C]; s32 v; };
struct gd_20_s32 { u8 pad[0x20]; s32 v; };
struct gd_24_s32 { u8 pad[0x24]; s32 v; };
struct gd_44_s32 { u8 pad[0x44]; s32 v; };
struct gd_48_s32 { u8 pad[0x48]; s32 v; };

void func_80099C8C(s32 arg0, s32 arg1, s32 arg2) {
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

    sp0 = arg2 + 204;
    sp4 = arg2 + 264;
    if ((((struct gd_20_s32 *)sp0)->v == 1) || (((struct gd_18_s32 *)sp4)->v == 0)) {
        sp8 = 0;
    } else {
        sp8 = (((struct gd_20_s32 *)sp0)->v - 1) - ((struct gd_1C_s32 *)sp4)->v;
    }
    if ((((struct gd_20_s32 *)sp0)->v == 1) || (((struct gd_20_s32 *)sp4)->v == 0)) {
        spC = 0;
    } else {
        spC = (((struct gd_20_s32 *)sp0)->v - 1) - ((struct gd_24_s32 *)sp4)->v;
    }
    sp10 = ((struct gd_18_s32 *)sp4)->v * ((struct gd_20_s32 *)sp0)->v;
    if (sp10 == 0) {
        sp14 = 0;
    } else {
        if (sp10 > 0) {
            sp10 = sp10 - sp8;
            sp14 = sp10 - (((struct gd_20_s32 *)sp0)->v * 32);
        } else {
            sp10 = sp10 + sp8;
            sp14 = sp10 + (((struct gd_20_s32 *)sp0)->v * 32);
        }
    }
    sp18 = ((struct gd_20_s32 *)sp4)->v * ((struct gd_20_s32 *)sp0)->v;
    if (sp18 == 0) {
        sp1C = 0;
    } else {
        if (sp18 > 0) {
            sp18 = sp18 - spC;
            sp1C = sp18 - (((struct gd_20_s32 *)sp0)->v * 32);
        } else {
            sp18 = sp18 + spC;
            sp1C = sp18 + (((struct gd_20_s32 *)sp0)->v * 32);
        }
    }
    sp20 = (((struct gd_20_s32 *)sp0)->v * 16) - 1;
    sp24 = ((struct gd_20_s32 *)sp0)->v * -16;
    sp28 = ((struct gd_44_s32 *)sp4)->v + sp10;
    if ((sp28 <= sp20) && (sp28 >= sp24)) {
        (*(s32 *)arg0) = ((struct gd_44_s32 *)sp4)->v + sp10;
    } else {
        (*(s32 *)arg0) = ((struct gd_44_s32 *)sp4)->v + sp14;
    }
    ((struct gd_44_s32 *)sp4)->v = *(s32 *)arg0;
    if (((struct gd_18_s32 *)sp0)->v != 0) {
        (*(s32 *)arg0) = (*(s32 *)arg0) << 1;
    }
    sp28 = ((struct gd_48_s32 *)sp4)->v + sp18;
    if ((sp28 <= sp20) && (sp28 >= sp24)) {
        (*(s32 *)arg1) = ((struct gd_48_s32 *)sp4)->v + sp18;
    } else {
        (*(s32 *)arg1) = ((struct gd_48_s32 *)sp4)->v + sp1C;
    }
    ((struct gd_48_s32 *)sp4)->v = *(s32 *)arg1;
    if (((struct gd_18_s32 *)sp0)->v != 0) {
        (*(s32 *)arg1) = (*(s32 *)arg1) << 1;
    }
}
