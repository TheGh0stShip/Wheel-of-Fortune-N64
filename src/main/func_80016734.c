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
struct gd_C_s32 { u8 pad[0xC]; s32 v; };
struct gd_10_s32 { u8 pad[0x10]; s32 v; };
struct gd_30_s32 { u8 pad[0x30]; s32 v; };
extern s32 D_800B96B4;
extern s32 D_800BA5D8;
s32 func_8000A850();
s32 func_8000ACE8();

struct n64dk_r12 func_80016734(s32 arg1) {
    s32 sp10;
    struct n64dk_r12 sp18;
    s32 sp28;

    sp28 = *(s32 *)((struct gd_30_s32 *)arg1)->v;
    sp18.w[1] = 1;
    sp18.w[0] = 0;
    for (;;) {
        sp10 = func_8000ACE8(arg1);
        if (sp10 == 0) {
            break;
        }
        switch (sp10) {
        case 8:
            D_800BA5D8 = ((struct gd_8_s32 *)((struct gd_30_s32 *)arg1)->v)->v + (((struct gd_C_s32 *)((struct gd_30_s32 *)arg1)->v)->v * 36);
            return sp18;
        }
    }
    ((struct gd_C_s32 *)((struct gd_30_s32 *)arg1)->v)->v = ((struct gd_C_s32 *)((struct gd_30_s32 *)arg1)->v)->v + D_800B96B4;
    if (((struct gd_C_s32 *)((struct gd_30_s32 *)arg1)->v)->v >= ((struct gd_10_s32 *)((struct gd_30_s32 *)arg1)->v)->v) {
        D_800BA5D8 = (((struct gd_8_s32 *)((struct gd_30_s32 *)arg1)->v)->v - 36) + (((struct gd_10_s32 *)((struct gd_30_s32 *)arg1)->v)->v * 36);
        func_8000A850(45);
        sp18.w[1] = 0;
        sp18.w[0] = 0;
        return sp18;
    }
    D_800BA5D8 = ((struct gd_8_s32 *)((struct gd_30_s32 *)arg1)->v)->v + (((struct gd_C_s32 *)((struct gd_30_s32 *)arg1)->v)->v * 36);
    return sp18;
}
