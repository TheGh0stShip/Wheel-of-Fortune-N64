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
struct gd_10_s32 { u8 pad[0x10]; s32 v; };
struct gd_240_s32 { u8 pad[0x240]; s32 v; };
s32 func_800A4C28();

s32 func_80089984(s32 arg0, s32 arg1) {
    s32 sp10;
    s32 sp14;
    s32 sp18;
    s32 sp1C;
    s32 sp20;
    s32 sp24;

    sp14 = ((struct gd_240_s32 *)arg0)->v;
    sp18 = ((struct gd_C_s32 *)arg0)->v * 16;
    sp1C = ((struct gd_8_s32 *)arg0)->v * 16;
    sp10 = func_800A4C28(24);
    sp20 = 4;
    if (sp20 == 0) {
        sp20 = 1;
    }
    if (sp20 == 3) {
        sp20 = 4;
    }
    sp24 = 1;
    ((struct gd_C_s32 *)sp10)->v = func_800A4C28(((((sp18 * sp1C) * sp20) * sp24) * sp24));
    (*(s32 *)sp10) = func_800A4C28((sp18 * sp1C));
    ((struct gd_4_s32 *)sp10)->v = func_800A4C28(((u32)(sp18 * sp1C) >> 2));
    ((struct gd_8_s32 *)sp10)->v = func_800A4C28(((u32)(sp18 * sp1C) >> 2));
    ((struct gd_10_s32 *)sp10)->v = 0;
    return sp10;
}
