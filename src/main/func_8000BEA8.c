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
struct gd_C_f32 { u8 pad[0xC]; f32 v; };
struct gd_10_f32 { u8 pad[0x10]; f32 v; };
struct gd_10_s16 { u8 pad[0x10]; s16 v; };
struct gd_12_s16 { u8 pad[0x12]; s16 v; };
struct gd_14_f32 { u8 pad[0x14]; f32 v; };
struct gd_14_s16 { u8 pad[0x14]; s16 v; };
struct gd_28_s32 { u8 pad[0x28]; s32 v; };
struct gd_2C_s32 { u8 pad[0x2C]; s32 v; };
struct gd_30_s32 { u8 pad[0x30]; s32 v; };
extern s32 D_800B3994;
extern f32 D_800B61AC;
extern u16 D_800B96B0;
extern s32 D_800B96B4;
extern s32 D_800BEE24;
s32 func_80002C34();
s32 func_8000315C();
s32 func_8000AAB0();
s32 func_8000ACE8();
s32 func_8000ADEC();
s32 func_8000AF00();
s32 func_8000B9FC();
s32 func_8000EE78();
s32 func_80026EB4();
s32 func_8003BEA8();
s32 func_8003C2A8(s32, s32, f32, s32);
s32 func_80041018();

struct n64dk_r12 func_8000BEA8(s32 arg1) {
    s32 sp10[12];
    f32 sp40;
    f32 sp44;
    f32 sp48;
    s32 sp50[16];
    struct n64dk_r12 sp90;
    s32 spA0;
    s32 spA4;

    spA0 = *(s32 *)((struct gd_30_s32 *)arg1)->v;
    sp90.w[1] = 1;
    sp90.w[0] = 0;
    for (;;) {
        spA4 = func_8000ACE8(arg1);
        if (spA4 == 0) {
            break;
        }
        switch (spA4) {
        case 8:
            sp90.w[1] = 1;
            sp90.w[0] = 2;
            return sp90;
        case 36:
            func_8000ADEC(arg1);
            func_8000AF00();
            func_8000B9FC(1);
            func_80026EB4();
            sp90.w[1] = 0;
            sp90.w[0] = 1;
            return sp90;
        case 34:
            func_8000ADEC(arg1);
            func_8000AF00();
            func_8000B9FC(1);
            func_8000EE78();
            sp90.w[1] = 0;
            sp90.w[0] = 1;
            return sp90;
        }
    }
    if (((D_800B96B0 & 0x1000) & 0xFFFF) != 0) {
        func_8000315C();
        func_8000AAB0(arg1, 36, 0);
        sp90.w[1] = 1;
        sp90.w[0] = 2;
        return sp90;
    }
    if ((func_80002C34(((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v) != 0) || (D_800B3994 >= 720)) {
        func_8000ADEC(arg1);
        func_8000AF00();
        func_8000B9FC(1);
        func_8000EE78();
        sp90.w[1] = 0;
        sp90.w[0] = 1;
        return sp90;
    }
    sp90.w[1] = 1;
    sp90.w[0] = 0;
    if (D_800B3994 >= 269) {
        if (D_800B3994 < 318) {
            D_800BEE24 = D_800BEE24 + (D_800B96B4 * 5);
        }
    }
    D_800B61AC = D_800B61AC - ((f32)D_800B96B4);
    D_800B3994 = D_800B3994 + D_800B96B4;
    func_8003C2A8(((s32)&sp10), 0, ((f32)D_800BEE24), 0);
    func_8003BEA8(((s32)&sp50), ((struct gd_28_s32 *)spA0)->v, ((struct gd_2C_s32 *)spA0)->v, ((struct gd_30_s32 *)spA0)->v);
    func_80041018(((s32)&sp10), ((s32)&sp50), ((s32)&sp10));
    ((struct gd_10_s16 *)spA0)->v = (s32)(((struct gd_C_f32 *)((struct gd_30_s32 *)arg1)->v)->v + sp40);
    ((struct gd_12_s16 *)spA0)->v = (s32)(((struct gd_10_f32 *)((struct gd_30_s32 *)arg1)->v)->v + sp44);
    ((struct gd_14_s16 *)spA0)->v = (s32)(((struct gd_14_f32 *)((struct gd_30_s32 *)arg1)->v)->v + sp48);
    if (D_800B3994 >= 721) {
        D_800B3994 = 720;
    }
    return sp90;
}
