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
extern s32 D_800B96B4;
s32 func_8000ACE8();
s32 func_800343F8();
s32 func_8003CE58();

struct n64dk_r12 func_800345E8(s32 arg1) {
    struct n64dk_r12 sp20;
    s32 sp30;
    s32 sp34;
    s32 sp38;

    sp38 = *(s32 *)((struct gd_30_s32 *)arg1)->v;
    for (;;) {
        sp30 = func_8000ACE8(arg1);
        if (sp30 == 0) {
            break;
        }
        switch (sp30) {
        case 8:
            ((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v = 10;
            break;
        }
    }
    ((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v--;
    if (((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v < 0) {
        if (((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v < -40) {
            sp20.w[1] = 0;
            sp20.w[0] = 1;
            return sp20;
        }
        if (((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v >= -9) {
            func_800343F8(80, 150, 60, 80, 30, 10, 2, 1);
        } else {
            func_800343F8(80, 150, 60, 80, 30, 10, 2, 1);
            sp20.w[1] = 1;
            sp20.w[0] = ((func_8003CE58() % -1) * ((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v) / D_800B96B4;
            return sp20;
        }
    } else {
        sp34 = 0;
        for (;;) {
            if (sp34 >= 4) {
                break;
            }
            func_800343F8(52, 15, 27, 15, 300, 150, 6, 3);
            sp34++;
        }
    }
    sp20.w[1] = 1;
    sp20.w[0] = (func_8003CE58() % 10) / D_800B96B4;
    return sp20;
}
