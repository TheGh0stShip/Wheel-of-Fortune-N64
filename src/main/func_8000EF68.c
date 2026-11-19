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
struct gd_C_f32 { u8 pad[0xC]; f32 v; };
struct gd_2C_f32 { u8 pad[0x2C]; f32 v; };
struct gd_30_s32 { u8 pad[0x30]; s32 v; };
extern f32 D_80000BA4;
extern f32 D_80000BA8;
extern f32 D_80000BAC;
extern f32 D_80000BB0;
extern f32 D_80057F44;
extern s32 D_80057F48;
extern u16 D_800B96B0;
extern s32 D_800B96B4;
extern s8 D_800B9956;
extern f32 D_800BCCF0;
s32 func_8000A850();
s32 func_8000ACE8();
s32 func_8000B5DC();
s32 func_8003CE58();

struct n64dk_r12 func_8000EF68(s32 arg1) {
    struct n64dk_r12 sp10;
    s32 pad0;
    s32 sp24;
    f32 sp28;
    s32 pad1;
    s32 pad2;
    s32 sp34;

    sp10.w[1] = 1;
    sp10.w[0] = 0;
    sp24 = func_8000B5DC(0x4010000, 0xFFFF0000);
    if (sp24 == 0) {
        return sp10;
    }
    for (;;) {
        sp34 = func_8000ACE8(arg1);
        if (sp34 == 0) {
            break;
        }
        switch (sp34) {
        case 8:
            ((struct gd_C_f32 *)((struct gd_30_s32 *)arg1)->v)->v = ((struct gd_2C_f32 *)sp24)->v;
            break;
        case 34:
            sp10.w[1] = 0;
            sp10.w[0] = 0;
            return sp10;
        }
    }
    sp28 = ((struct gd_C_f32 *)((struct gd_30_s32 *)arg1)->v)->v - (((f32)D_800B9956) / D_80057F44);
    if (sp28 > 0.0f) {
        sp28 = sp28 * D_80000BA4;
    }
    sp28 = sp28 - ((struct gd_2C_f32 *)sp24)->v;
    sp28 = sp28 / ((f32)(12 / D_800B96B4));
    D_800BCCF0 = (sp28 * D_80000BA8) * D_80000BAC;
    ((struct gd_2C_f32 *)sp24)->v = ((struct gd_2C_f32 *)sp24)->v + sp28;
    if (((D_800B96B0 & 0xA000) & 0xFFFF) != 0) {
        D_800BCCF0 = ((f32)(func_8003CE58() % 40)) + D_80000BB0;
        func_8000A850(29);
        sp10.w[1] = 0;
        sp10.w[0] = 0;
    }
    if (((f32)D_80057F48) < D_800BCCF0) {
        func_8000A850(29);
        sp10.w[1] = 0;
        sp10.w[0] = 0;
    }
    return sp10;
}
