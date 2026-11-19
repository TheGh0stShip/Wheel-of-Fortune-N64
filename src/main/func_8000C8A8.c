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
struct gd_12_s16 { u8 pad[0x12]; s16 v; };
struct gd_12_u16 { u8 pad[0x12]; u16 v; };
struct gd_14_s16 { u8 pad[0x14]; s16 v; };
struct gd_14_u16 { u8 pad[0x14]; u16 v; };
struct gd_30_f32 { u8 pad[0x30]; f32 v; };
struct gd_30_s32 { u8 pad[0x30]; s32 v; };
extern f64 D_80000AD4;
extern f64 D_80000ADC;
extern s32 D_800B619C;
extern u16 D_800B96B0;
extern u16 D_800B9954;
s32 func_8000ACE8();

struct n64dk_r12 func_8000C8A8(s32 arg1) {
    struct n64dk_r12 sp10;
    s32 sp20;
    s32 sp24;

    sp20 = *(s32 *)((struct gd_30_s32 *)arg1)->v;
    sp10.w[1] = 1;
    sp10.w[0] = 0;
    for (;;) {
        sp24 = func_8000ACE8(arg1);
        if (sp24 == 0) {
            break;
        }
        switch (sp24) {
        case 8:
            ((struct gd_12_s16 *)sp20)->v = -140;
            ((struct gd_14_s16 *)sp20)->v = -380;
        }
    }
    sp10.w[1] = 1;
    sp10.w[0] = 0;
    if (((D_800B96B0 & 0x8000) & 0xFFFF) != 0) {
        D_800B619C++;
        if (D_800B619C >= 4) {
            D_800B619C = 0;
        }
    }
    if (((D_800B96B0 & 0x4000) & 0xFFFF) != 0) {
        D_800B619C--;
        if (D_800B619C < 0) {
            D_800B619C = 3;
        }
    }
    if (((D_800B9954 & 16) & 0xFFFF) != 0) {
        ((struct gd_30_f32 *)sp20)->v = (f32)(((f64)((struct gd_30_f32 *)sp20)->v) - D_80000AD4);
    }
    if (((D_800B9954 & 32) & 0xFFFF) != 0) {
        ((struct gd_30_f32 *)sp20)->v = (f32)(((f64)((struct gd_30_f32 *)sp20)->v) + D_80000ADC);
    }
    if (((D_800B9954 & 512) & 0xFFFF) != 0) {
        ((struct gd_14_s16 *)sp20)->v = ((struct gd_14_u16 *)sp20)->v + 10;
    }
    if (((D_800B9954 & 256) & 0xFFFF) != 0) {
        ((struct gd_14_s16 *)sp20)->v = ((struct gd_14_u16 *)sp20)->v - 10;
    }
    if (((D_800B9954 & 2048) & 0xFFFF) != 0) {
        ((struct gd_12_s16 *)sp20)->v = ((struct gd_12_u16 *)sp20)->v + 10;
    }
    if (((D_800B9954 & 1024) & 0xFFFF) != 0) {
        ((struct gd_12_s16 *)sp20)->v = ((struct gd_12_u16 *)sp20)->v - 10;
    }
    return sp10;
}
