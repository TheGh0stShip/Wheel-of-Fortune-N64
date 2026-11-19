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

struct gd_1F8_s32 { u8 pad[0x1F8]; s32 v; };
struct gd_208_s32 { u8 pad[0x208]; s32 v; };
struct gd_210_s32 { u8 pad[0x210]; s32 v; };
s32 func_800A3168();
s32 func_800A3460();
s32 func_800A4A18();

s32 func_800A2B40(s32 arg0) {
    s32 sp18;
    s32 sp1C;
    s32 sp20;
    s32 sp24;
    s32 sp28;
    s32 sp2C;
    s32 sp30;
    s32 sp34;
    s32 sp38;

    sp18 = arg0 + 492;
    sp1C = arg0 + 496;
    sp20 = arg0 + 488;
    sp24 = arg0 + 484;
    sp38 = ((struct gd_1F8_s32 *)arg0)->v;
    if (sp38 == 0) {
        return func_800A3168((*(s32 *)sp18), (*(s32 *)sp1C), sp20, sp24, arg0);
    }
    if (sp38 == -1) {
        ((struct gd_210_s32 *)arg0)->v = 0;
        sp34 = *(s32 *)sp18;
        sp28 = func_800A4A18(((s32)&sp2C), 1, 4, ((struct gd_208_s32 *)arg0)->v);
        if (sp28 != 4) {
            return 0;
        }
        if ((sp2C == 442) || (sp2C == 443)) {
            ((struct gd_1F8_s32 *)arg0)->v = 1;
            sp30 = func_800A3460(arg0, sp2C);
            return sp30;
        } else {
            ((struct gd_1F8_s32 *)arg0)->v = 0;
            (*(s32 *)(*(s32 *)sp18)) = sp2C;
            (*(s32 *)sp20) = 1;
            sp30 = func_800A3168((*(s32 *)sp18), (*(s32 *)sp1C), sp20, sp24, arg0);
            (*(s32 *)sp24) = *(s32 *)sp18;
            return sp30;
        }
    }
    sp30 = func_800A3460(arg0, 0);
    return sp30;
}
