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

extern f32 D_800007CC;
extern s32 D_800BEDA8;
extern s32 D_800BEDF8;
s32 func_80009C98();

void func_80009108(f32 arg0) {
    s32 sp10;

    if (arg0 == D_800007CC) {
        D_800BEDA8 = D_800BEDA8 + func_80009C98(24);
    } else {
        sp10 = (s32)arg0;
        if (sp10 < 0) {
            sp10 = sp10 * -1;
        }
        sp10 = sp10 % 360;
        D_800BEDA8 = sp10 / 15;
        D_800BEDF8 = sp10 / 5;
    }
    if (D_800BEDA8 >= 24) {
        D_800BEDA8 = D_800BEDA8 % 24;
    }
}
