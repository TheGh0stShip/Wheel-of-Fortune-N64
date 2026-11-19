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
struct gd_10_s16 { u8 pad[0x10]; s16 v; };
struct gd_12_s16 { u8 pad[0x12]; s16 v; };
struct gd_14_s16 { u8 pad[0x14]; s16 v; };
struct gd_18_f32 { u8 pad[0x18]; f32 v; };
struct gd_28_s32 { u8 pad[0x28]; s32 v; };
struct gd_2C_s32 { u8 pad[0x2C]; s32 v; };
struct gd_30_s32 { u8 pad[0x30]; s32 v; };
struct gd_48_s32 { u8 pad[0x48]; s32 v; };
extern f32 D_80001558;
extern s32 func_80020150;
s32 func_8000B3B0();

s32 func_800211E4(s32 arg0, s32 arg1, f32 arg2, f32 arg3) {
    s32 sp10;
    s32 sp14;

    sp10 = 0;
    if (arg0 != 0) {
        sp10 = ((struct gd_4_s32 *)arg0)->v;
    }
    sp14 = func_8000B3B0(sp10, ((s32)&func_80020150), 0x5010000);
    ((struct gd_18_f32 *)sp14)->v = D_80001558;
    ((struct gd_10_s16 *)sp14)->v = (s32)arg2;
    ((struct gd_12_s16 *)sp14)->v = (s32)arg3;
    ((struct gd_14_s16 *)sp14)->v = 0;
    ((struct gd_28_s32 *)sp14)->v = 0;
    ((struct gd_2C_s32 *)sp14)->v = 0;
    ((struct gd_30_s32 *)sp14)->v = 0;
    ((struct gd_48_s32 *)sp14)->v = 0;
    return sp14;
}
