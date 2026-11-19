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

f64 func_8003EB90(f64 arg0, s32 *arg2) {
    f64 var_f0_23;
    f64 var_f2_65;

    *arg2 = 0;
    if (arg0 == 0.0) {
        return arg0;
    }
    if (arg0 > 0.0) {
        var_f0_23 = arg0;
    } else {
        var_f0_23 = -arg0;
    }
    if (var_f0_23 >= 1.0) {
        do {
            var_f0_23 *= 0.5;
            *arg2 += 1;
        } while (var_f0_23 >= 1.0);
    }
    if (var_f0_23 < 0.5) {
        do {
            var_f0_23 *= 2.0;
            *arg2 -= 1;
        } while (var_f0_23 < 0.5);
    }
    if (arg0 > 0.0) {
        var_f2_65 = var_f0_23;
    } else {
        var_f2_65 = -var_f0_23;
    }
    return var_f2_65;
}
