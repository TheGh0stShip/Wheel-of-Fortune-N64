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

M2C_UNK *func_80042AB8(void *arg0, u8 arg1, u8 arg2, u8 arg3) {
    M2C_UNK *temp_v1_8;

    temp_v1_8 = M2C_FIELD(arg0, M2C_UNK **, 0x6C);
    if (temp_v1_8 != NULL) {
        M2C_FIELD(arg0, M2C_UNK **, 0x6C) = (M2C_UNK *) M2C_FIELD(temp_v1_8, M2C_UNK **, 0);
        M2C_FIELD(temp_v1_8, M2C_UNK **, 0) = NULL;
        if (M2C_FIELD(arg0, M2C_UNK **, 0x64) == NULL) {
            M2C_FIELD(arg0, M2C_UNK **, 0x64) = temp_v1_8;
        } else {
            *M2C_FIELD(arg0, M2C_UNK **, 0x68) = temp_v1_8;
        }
        M2C_FIELD(arg0, M2C_UNK **, 0x68) = temp_v1_8;
        M2C_FIELD(temp_v1_8, s8 *, 0x31) = (s8) (arg3);
        M2C_FIELD(temp_v1_8, s8 *, 0x32) = (s8) (arg1);
        M2C_FIELD(temp_v1_8, s8 *, 0x33) = (s8) (arg2);
        M2C_FIELD(temp_v1_8, M2C_UNK **, 0x14) = temp_v1_8;
    }
    return temp_v1_8;
}
