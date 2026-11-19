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

struct n64dk_r12 { s32 w[3]; };
struct gd_4_s32 { u8 pad[0x4]; s32 v; };
struct gd_30_s32 { u8 pad[0x30]; s32 v; };
struct n64dk_a800B9990 { s32 m0; u8 pad4[0x110]; };
extern struct n64dk_a800B9990 D_800B9990[];
extern s32 D_800B96A8;
extern s32 D_800FB808;
s32 func_8000AAB0();
s32 func_8000ACE8();
struct n64dk_r12 func_8000FC3C();
s32 func_80016098();
s32 func_80032AD4();
s32 func_80032B10();

struct n64dk_r12 func_8000FDFC(s32 arg1) {
    struct n64dk_r12 sp10;
    s32 sp20;
    s32 sp24;
    s8 pad0;

    sp20 = *(s32 *)((struct gd_30_s32 *)arg1)->v;
    for (;;) {
        sp24 = func_8000ACE8(arg1);
        if (sp24 == 0) {
            break;
        }
        switch (sp24) {
        case 8:
            func_80016098();
            func_80032B10();
            func_80032AD4(1);
            ((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v = 0;
            D_800B96A8++;
            func_8000AAB0(arg1, 41, 0);
            return func_8000FC3C(arg1);
        case 41:
            D_800B96A8 = D_800B96A8 + (D_800B9990[D_800FB808].m0 / 0x1388);
            return func_8000FC3C(arg1);
        case 34:
            sp10.w[1] = 0;
            sp10.w[0] = 0;
            return sp10;
        }
    }
    return func_8000FC3C(arg1);
}
