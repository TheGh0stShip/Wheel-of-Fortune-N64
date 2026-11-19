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

extern s32 D_8004B718;
extern s32 D_800A509C;
s32 func_80039718();
s32 func_80039778();
s32 func_800397D8();
s32 func_80049FA8();

void func_80003014(s32 arg0, register s32 arg1, register s32 arg2, register s32 arg3) {
    u8 sp10;
    u8 sp11;
    s16 sp12;

    sp10 = arg1;
    sp11 = arg2;
    sp12 = arg3;
    func_80049FA8(D_8004B718, (*(s16 *)((arg0 * 2) + D_800A509C)));
    func_800397D8(D_8004B718, sp10);
    func_80039778(D_8004B718, sp11);
    func_80039718(D_8004B718, sp12);
}
