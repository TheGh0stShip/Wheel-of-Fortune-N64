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

s32 func_80007EEC();                         /* extern */
extern s32 D_800B619C;
extern s32 D_800B96A0;
extern s32 D_800B9980;
extern s32 D_800B9CF8;
extern s32 D_800B9CFC;
extern s32 D_800B9D00;
extern s32 D_800FB808;

void func_8000963C(s32 arg0) {
    D_800B9980 = 0;
    D_800B96A0 = 0;
    if (arg0 == 0) {
        if (func_80007EEC(0) == 2) {
            D_800B9CF8 = 0;
        } else {
            D_800B9CF8 = 1;
        }
        D_800B9CFC = 1;
        D_800B9D00 = 1;
        D_800FB808++;
        if (D_800FB808 >= 3) {
            D_800FB808 = 0;
        }
        return;
    }
    D_800FB808 = D_800B619C % 3;
}
