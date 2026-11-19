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

M2C_UNK alLink();                  /* extern */
M2C_UNK alUnlink();                        /* extern */
s32 osSetIntMask();                              /* extern */

void func_8003F874(void *arg0) {
    s32 pad[2]; /* n64dk: frame padding, reconstruction scaffolding */
    s32 sp2C;
    M2C_UNK *temp_s1_18;
    M2C_UNK *var_s0_14;

    sp2C = osSetIntMask(1);
    var_s0_14 = M2C_FIELD(arg0, M2C_UNK **, 8);
    if (var_s0_14 != NULL) {
        do {
            temp_s1_18 = *var_s0_14;
            alUnlink(var_s0_14);
            alLink(var_s0_14, arg0);
            var_s0_14 = temp_s1_18;
        } while (temp_s1_18 != NULL);
    }
    osSetIntMask(sp2C);
}
