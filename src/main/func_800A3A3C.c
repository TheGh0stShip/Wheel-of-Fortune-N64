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

struct gd_204_s32 { u8 pad[0x204]; s32 v; };
struct gd_208_s32 { u8 pad[0x208]; s32 v; };
s32 func_800A46FC();
s32 func_800A4888();
s32 func_800A4920();
s32 func_800A4A18();

s32 func_800A3A3C(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp10;
    s32 sp18[2];
    s32 sp20;
    u8 sp24;
    s32 sp28;

    sp10 = func_800A4A18(((s32)&sp18), 1, 8, ((struct gd_208_s32 *)arg2)->v);
    if (sp10 < 8) {
        ((struct gd_204_s32 *)arg2)->v = 1;
        return 1;
    }
    func_800A46FC(((s32)&sp18), ((s32)&sp24), ((s32)&sp20));
    sp28 = func_800A4920(sp24, sp20, arg0);
    func_800A4888((((s32)&sp18) + 5), arg1);
    (*(s32 *)arg1) = (*(s32 *)arg1) * 50;
    return 0;
}
