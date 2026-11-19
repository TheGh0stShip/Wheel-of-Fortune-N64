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
struct gd_8_s32 { u8 pad[0x8]; s32 v; };
struct gd_10_s16 { u8 pad[0x10]; s16 v; };
struct gd_12_s16 { u8 pad[0x12]; s16 v; };
struct gd_14_s16 { u8 pad[0x14]; s16 v; };
struct gd_30_s32 { u8 pad[0x30]; s32 v; };
extern s32 D_800BEE24;
s32 func_8000ACE8();
s32 func_8003BEA8(s32, s32, f32, s32);
s32 func_8003C2A8(s32, s32, s32, f32);
s32 func_80041018();

struct n64dk_r12 func_8000C50C(s32 arg1) {
    s32 sp10[12];
    f32 sp40;
    f32 sp44;
    f32 sp48;
    s32 sp50[16];
    struct n64dk_r12 sp90;
    s32 spA0;
    s32 spA4;
    s8 pad0;

    spA0 = *(s32 *)((struct gd_30_s32 *)arg1)->v;
    for (;;) {
        spA4 = func_8000ACE8(arg1);
        if (spA4 == 0) {
            break;
        }
        switch (spA4) {
        case 34:
        case 36:
            sp90.w[1] = 0;
            sp90.w[0] = 1;
            return sp90;
        }
    }
    func_8003C2A8(((s32)&sp10), 0, 0, ((f32)D_800BEE24));
    func_8003BEA8(((s32)&sp50), 0, ((f32)(((struct gd_8_s32 *)((struct gd_30_s32 *)arg1)->v)->v * 15)), 0);
    func_80041018(((s32)&sp10), ((s32)&sp50), ((s32)&sp10));
    ((struct gd_10_s16 *)spA0)->v = (s32)sp40;
    ((struct gd_12_s16 *)spA0)->v = (s32)sp44;
    ((struct gd_14_s16 *)spA0)->v = (s32)sp48;
    sp90.w[1] = 1;
    sp90.w[0] = 0;
    return sp90;
}
