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

struct gd_10_s32 { u8 pad[0x10]; s32 v; };
struct gd_14_f32 { u8 pad[0x14]; f32 v; };
struct gd_18_f32 { u8 pad[0x18]; f32 v; };
struct gd_1C_f32 { u8 pad[0x1C]; f32 v; };
struct gd_20_s32 { u8 pad[0x20]; s32 v; };
struct gd_30_s32 { u8 pad[0x30]; s32 v; };
extern f32 D_80001A74;
extern s32 func_80033CF8;
extern s32 func_80034028;
s32 func_8000A56C();
s32 func_80015848();
s32 func_8003CE58();

void func_800343F8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    s32 sp10;
    s32 sp14;

    sp14 = func_8000A56C(((s32)&func_80034028), 0x5030000);
    sp10 = func_80015848(sp14, 0, ((s32)&func_80033CF8), 0x5030000);
    ((struct gd_10_s32 *)((struct gd_30_s32 *)sp14)->v)->v = ((func_8003CE58() % arg6) - arg7) + arg7;
    ((struct gd_1C_f32 *)((struct gd_30_s32 *)sp14)->v)->v = ((f32)(((func_8003CE58() % arg4) - arg5) + arg5)) / D_80001A74;
    ((struct gd_20_s32 *)((struct gd_30_s32 *)sp14)->v)->v = 0;
    ((struct gd_14_f32 *)((struct gd_30_s32 *)sp14)->v)->v = (f32)((func_8003CE58() % arg1) + arg0);
    ((struct gd_18_f32 *)((struct gd_30_s32 *)sp14)->v)->v = (f32)((func_8003CE58() % arg3) + arg2);
}
