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
struct gd_10_s32 { u8 pad[0x10]; s32 v; };
struct gd_30_s32 { u8 pad[0x30]; s32 v; };
struct n64dk_a8005B368 { s32 m0; s32 m4; u8 pad8[0x10]; s32 m18; u8 pad1C[0xC]; };
extern struct n64dk_a8005B368 D_8005B368[];
struct n64dk_a8005B4CC { s32 m0; u8 pad4[0x4]; s32 m8; u8 padC[0x1C]; };
extern struct n64dk_a8005B4CC D_8005B4CC[];
extern s32 D_800B96B4;
s32 func_8000ACE8();

struct n64dk_r12 func_80029C98(s32 arg1) {
    s32 sp10;
    s32 sp14;
    s32 sp18;
    struct n64dk_r12 sp20;
    s8 pad0;

    sp20.w[1] = 1;
    sp20.w[0] = (3 / D_800B96B4) - 1;
    for (;;) {
        sp10 = func_8000ACE8(arg1);
        if (sp10 == 0) {
            break;
        }
        switch (sp10) {
        case 8:
            ((struct gd_10_s32 *)((struct gd_30_s32 *)arg1)->v)->v = 0;
        }
    }
    ((struct gd_10_s32 *)((struct gd_30_s32 *)arg1)->v)->v = ((struct gd_10_s32 *)((struct gd_30_s32 *)arg1)->v)->v + 1;
    sp18 = ((struct gd_10_s32 *)((struct gd_30_s32 *)arg1)->v)->v;
    if (sp18 >= 17) {
        sp14 = 0;
        for (;;) {
            if (sp14 >= 9) {
                break;
            }
            D_8005B368[sp14].m18 = 0;
            sp14++;
        }
        sp20.w[1] = 0;
        sp20.w[0] = 0;
        return sp20;
    }
    sp14 = 0;
    for (;;) {
        if (sp14 >= 9) {
            break;
        }
        if (D_8005B368[sp14].m18 != 0) {
            D_8005B368[sp14].m18 = D_8005B368[sp14].m18 + (D_8005B368[sp14].m0 * 2);
            D_8005B368[sp14].m4 = 15 - sp18;
            if (D_8005B368[sp14].m4 <= 0) {
                D_8005B368[sp14].m18 = 0;
            }
        }
        D_8005B4CC[sp14].m0 = 61 - sp18;
        D_8005B4CC[sp14].m8 = sp18;
        if (sp18 >= 16) {
            D_8005B4CC[sp14].m8 = 15;
        }
        sp14++;
    }
    return sp20;
}
