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
struct gd_28_f32 { u8 pad[0x28]; f32 v; };
struct gd_2C_f32 { u8 pad[0x2C]; f32 v; };
struct gd_30_s32 { u8 pad[0x30]; s32 v; };
struct n64dk_a800B39A0 { f32 m0; f32 m4; };
extern struct n64dk_a800B39A0 D_800B39A0[];
extern f64 D_80000EAC;
extern f64 D_80000EB4;
extern f64 D_80000EBC;
extern f64 D_80000EC4;
extern f32 D_80057F7C;
extern f32 D_80057F80;
extern u16 D_800B9954;
extern s32 D_800FB808;
s32 func_8000B5DC();

struct n64dk_r12 func_80017938(s32 arg1) {
    struct n64dk_r12 sp10;
    s32 pad0;
    s32 sp24;

    sp10.w[1] = 1;
    sp10.w[0] = 0;
    if (((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v != D_800FB808) {
        return sp10;
    }
    if (((D_800B9954 & 1) & 0xFFFF) != 0) {
        D_800B39A0[D_800FB808].m4 = (f32)(((f64)D_800B39A0[D_800FB808].m4) - D_80000EAC);
    }
    if (((D_800B9954 & 2) & 0xFFFF) != 0) {
        D_800B39A0[D_800FB808].m4 = (f32)(((f64)D_800B39A0[D_800FB808].m4) + D_80000EB4);
    }
    if (((D_800B9954 & 4) & 0xFFFF) != 0) {
        D_800B39A0[D_800FB808].m0 = (f32)(((f64)D_800B39A0[D_800FB808].m0) - D_80000EBC);
    }
    if (((D_800B9954 & 8) & 0xFFFF) != 0) {
        D_800B39A0[D_800FB808].m0 = (f32)(((f64)D_800B39A0[D_800FB808].m0) + D_80000EC4);
    }
    sp24 = func_8000B5DC(0x3000000, 0xFF000000);
    ((struct gd_28_f32 *)sp24)->v = D_80057F7C + D_800B39A0[D_800FB808].m0;
    ((struct gd_2C_f32 *)sp24)->v = D_80057F80 + D_800B39A0[D_800FB808].m4;
    return sp10;
}
