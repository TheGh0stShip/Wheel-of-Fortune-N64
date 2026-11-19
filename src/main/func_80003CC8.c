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

struct gd_4_s32 { u8 pad[0x4]; s32 v; };
struct gd_8_s32 { u8 pad[0x8]; s32 v; };
struct gd_C_s32 { u8 pad[0xC]; s32 v; };
struct gd_10_s32 { u8 pad[0x10]; s32 v; };
extern s32 D_8004B7A8;
extern s32 D_8004B7AC;
extern s32 D_800BA598;
extern s32 D_800BA5CC;
extern s32 D_800BA5D0;
extern s32 D_800BC700;
s32 func_8003A538();
s32 func_8003A568();
s32 func_8003FF78();
s32 func_80045628();

s32 func_80003CC8(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp20;
    s32 sp24;
    s32 sp28;
    s32 sp2C;
    s32 sp30;
    s32 sp34;

    sp34 = 0;
    sp30 = D_800BA5CC;
    sp28 = arg0 + arg1;
    for (;;) {
        if (sp30 == 0) {
            break;
        }
        sp2C = ((struct gd_8_s32 *)sp30)->v + 2048;
        if ((u32)((struct gd_8_s32 *)sp30)->v > (u32)arg0) {
            break;
        } else {
            if (sp28 <= sp2C) {
                ((struct gd_C_s32 *)sp30)->v = D_8004B7A8;
                sp20 = (((struct gd_10_s32 *)sp30)->v + arg0) - ((struct gd_8_s32 *)sp30)->v;
                return func_8003FF78(sp20);
            }
        }
        sp34 = sp30;
        sp30 = *(s32 *)sp30;
    }
    sp30 = D_800BA5D0;
    D_800BA5D0 = *(s32 *)sp30;
    func_8003A538(sp30);
    if (sp34 != 0) {
        func_8003A568(sp30, sp34);
    } else {
        if (D_800BA5CC != 0) {
            sp34 = D_800BA5CC;
            D_800BA5CC = sp30;
            (*(s32 *)sp30) = sp34;
            ((struct gd_4_s32 *)sp30)->v = 0;
            ((struct gd_4_s32 *)sp34)->v = sp30;
        } else {
            D_800BA5CC = sp30;
            (*(s32 *)sp30) = 0;
            ((struct gd_4_s32 *)sp30)->v = 0;
        }
    }
    sp20 = ((struct gd_10_s32 *)sp30)->v;
    sp24 = arg0 & 1;
    arg0 = arg0 - sp24;
    ((struct gd_8_s32 *)sp30)->v = arg0;
    ((struct gd_C_s32 *)sp30)->v = D_8004B7A8;
    func_80045628((((D_8004B7AC++) * 24) + ((s32)&D_800BC700)), 0, 0, arg0, sp20, 2048, ((s32)&D_800BA598));
    return func_8003FF78(sp20) + sp24;
}
