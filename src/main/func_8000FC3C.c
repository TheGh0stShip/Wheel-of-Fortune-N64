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

struct n64dk_r12 { s32 w[3]; };
struct gd_C_f32 { u8 pad[0xC]; f32 v; };
struct gd_10_f32 { u8 pad[0x10]; f32 v; };
struct gd_2C_f32 { u8 pad[0x2C]; f32 v; };
struct gd_30_s32 { u8 pad[0x30]; s32 v; };
extern f32 D_80000BEC;
extern f64 D_80000BF0;
extern f32 D_80000BF8;
extern f32 D_80000BFC;
extern s32 func_8000F84C;
extern s32 D_800B96B4;
extern f32 D_800BCCF0;
s32 func_8000A56C();
s32 func_8000A850();

struct n64dk_r12 func_8000FC3C(s32 arg1) {
    struct n64dk_r12 sp10;
    s32 sp20;

    sp20 = *(s32 *)((struct gd_30_s32 *)arg1)->v;
    sp10.w[1] = 1;
    sp10.w[0] = 0;
    if (((struct gd_C_f32 *)((struct gd_30_s32 *)arg1)->v)->v <= 0.0f) {
        func_8000A56C(((s32)&func_8000F84C), 0x4000000);
        sp10.w[1] = 0;
        sp10.w[0] = 0;
    } else {
        ((struct gd_2C_f32 *)sp20)->v = ((struct gd_2C_f32 *)sp20)->v - ((((struct gd_C_f32 *)((struct gd_30_s32 *)arg1)->v)->v / D_80000BEC) * ((f32)D_800B96B4));
        ((struct gd_C_f32 *)((struct gd_30_s32 *)arg1)->v)->v = (f32)(((f64)((struct gd_C_f32 *)((struct gd_30_s32 *)arg1)->v)->v) - (((f64)D_800B96B4) * D_80000BF0));
    }
    if (((struct gd_C_f32 *)((struct gd_30_s32 *)arg1)->v)->v <= D_80000BF8) {
        if (((struct gd_10_f32 *)((struct gd_30_s32 *)arg1)->v)->v > D_80000BFC) {
            func_8000A850(4);
        }
    }
    D_800BCCF0 = ((struct gd_C_f32 *)((struct gd_30_s32 *)arg1)->v)->v;
    ((struct gd_10_f32 *)((struct gd_30_s32 *)arg1)->v)->v = ((struct gd_C_f32 *)((struct gd_30_s32 *)arg1)->v)->v;
    return sp10;
}
