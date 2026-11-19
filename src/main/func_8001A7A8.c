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

s32 func_800076E0();
s32 func_80009A74();
s32 func_8001A6DC();

s32 func_8001A7A8(s32 arg0) {
    s32 sp10;
    s32 sp14;
    u8 sp18;

    sp18 = 32;
    sp14 = func_80009A74(arg0);
    sp10 = 0;
    for (;;) {
        if (sp10 >= sp14) {
            break;
        }
        if (func_800076E0((*(u8 *)(arg0 + sp10))) > 0) {
            sp18 = *(u8 *)(arg0 + sp10);
            break;
        }
        sp10++;
    }
    if (sp18 == 32) {
        sp18 = func_8001A6DC(arg0);
    }
    return sp18;
}
