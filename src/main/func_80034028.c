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
struct gd_8_s32 { u8 pad[0x8]; s32 v; };
struct gd_10_s16 { u8 pad[0x10]; s16 v; };
struct gd_10_s32 { u8 pad[0x10]; s32 v; };
struct gd_12_s16 { u8 pad[0x12]; s16 v; };
struct gd_14_f32 { u8 pad[0x14]; f32 v; };
struct gd_18_f32 { u8 pad[0x18]; f32 v; };
struct gd_1C_f32 { u8 pad[0x1C]; f32 v; };
struct gd_20_f32 { u8 pad[0x20]; f32 v; };
struct gd_30_s32 { u8 pad[0x30]; s32 v; };
struct gd_44_s32 { u8 pad[0x44]; s32 v; };
extern s32 D_8005C948;
extern f32 D_8005C958;
extern f32 D_8005C95C;
extern s32 D_800B96B4;
s32 func_8000ACE8();

struct n64dk_r12 func_80034028(s32 arg1) {
    struct n64dk_r12 sp10;
    s32 sp20;
    s32 sp24;
    s32 sp28;

    sp28 = *(s32 *)((struct gd_30_s32 *)arg1)->v;
    for (;;) {
        sp20 = func_8000ACE8(arg1);
        if (sp20 == 0) {
            break;
        }
        switch (sp20) {
        case 8:
            ((struct gd_8_s32 *)((struct gd_30_s32 *)arg1)->v)->v = 0;
            ((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v = 0;
            break;
        }
    }
    ((struct gd_8_s32 *)((struct gd_30_s32 *)arg1)->v)->v = ((struct gd_8_s32 *)((struct gd_30_s32 *)arg1)->v)->v + D_800B96B4;
    if (((struct gd_8_s32 *)((struct gd_30_s32 *)arg1)->v)->v >= 4) {
        ((struct gd_8_s32 *)((struct gd_30_s32 *)arg1)->v)->v = ((struct gd_8_s32 *)((struct gd_30_s32 *)arg1)->v)->v % 4;
        ((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v++;
        if (((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v >= 4) {
            ((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v = 0;
            ((struct gd_10_s32 *)((struct gd_30_s32 *)arg1)->v)->v--;
            if (((struct gd_10_s32 *)((struct gd_30_s32 *)arg1)->v)->v < 0) {
                sp10.w[1] = 0;
                sp10.w[0] = 1;
                return sp10;
            }
        }
    }
    sp24 = 0;
    for (;;) {
        if (sp24 >= D_800B96B4) {
            break;
        }
        ((struct gd_20_f32 *)((struct gd_30_s32 *)arg1)->v)->v = ((struct gd_20_f32 *)((struct gd_30_s32 *)arg1)->v)->v + D_8005C958;
        ((struct gd_1C_f32 *)((struct gd_30_s32 *)arg1)->v)->v = ((struct gd_1C_f32 *)((struct gd_30_s32 *)arg1)->v)->v - D_8005C95C;
        ((struct gd_14_f32 *)((struct gd_30_s32 *)arg1)->v)->v = ((struct gd_14_f32 *)((struct gd_30_s32 *)arg1)->v)->v + ((struct gd_1C_f32 *)((struct gd_30_s32 *)arg1)->v)->v;
        ((struct gd_18_f32 *)((struct gd_30_s32 *)arg1)->v)->v = ((struct gd_18_f32 *)((struct gd_30_s32 *)arg1)->v)->v + ((struct gd_20_f32 *)((struct gd_30_s32 *)arg1)->v)->v;
        sp24++;
    }
    ((struct gd_10_s16 *)sp28)->v = (s32)((struct gd_14_f32 *)((struct gd_30_s32 *)arg1)->v)->v;
    ((struct gd_12_s16 *)sp28)->v = (s32)((struct gd_18_f32 *)((struct gd_30_s32 *)arg1)->v)->v;
    if ((((struct gd_10_s16 *)sp28)->v < 0) || ((((struct gd_12_s16 *)sp28)->v < 0) || ((((struct gd_10_s16 *)sp28)->v >= 321) || (((struct gd_12_s16 *)sp28)->v >= 201)))) {
        sp10.w[1] = 0;
        sp10.w[0] = 1;
        return sp10;
    }
    ((struct gd_44_s32 *)sp28)->v = *(s32 *)((((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v * 4) + ((s32)&D_8005C948));
    sp10.w[1] = 1;
    sp10.w[0] = 0;
    return sp10;
}
