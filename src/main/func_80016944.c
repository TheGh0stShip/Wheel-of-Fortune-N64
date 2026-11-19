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

struct gd_8_s32 { u8 pad[0x8]; s32 v; };
struct gd_C_s32 { u8 pad[0xC]; s32 v; };
struct gd_10_s16 { u8 pad[0x10]; s16 v; };
struct gd_10_s32 { u8 pad[0x10]; s32 v; };
struct gd_12_s16 { u8 pad[0x12]; s16 v; };
struct gd_14_s16 { u8 pad[0x14]; s16 v; };
struct gd_18_f32 { u8 pad[0x18]; f32 v; };
struct gd_28_f32 { u8 pad[0x28]; f32 v; };
struct gd_2C_f32 { u8 pad[0x2C]; f32 v; };
struct gd_30_f32 { u8 pad[0x30]; f32 v; };
struct gd_30_s32 { u8 pad[0x30]; s32 v; };
struct gd_48_s32 { u8 pad[0x48]; s32 v; };
struct n64dk_a80057F52 { u16 m0; u8 pad2[0x2]; u16 m4; u8 pad6[0x2]; u16 m8; u8 padA[0x16]; };
extern struct n64dk_a80057F52 D_80057F52[];
struct n64dk_a80057F5C { f32 m0; f32 m4; f32 m8; s32 mC; s32 m10; u8 pad14[0xC]; };
extern struct n64dk_a80057F5C D_80057F5C[];
extern f32 D_80000E88;
extern s32 func_80016734;
extern f32 D_800B6BE8;
extern f32 D_800B6BEC;
extern f32 D_800B6BF0;
extern s32 D_800BA2BC;
extern s32 D_800BA5D8;
s32 func_8000A4A4();
s32 func_8000A56C();
s32 func_8000A990();

void func_80016944(s32 arg0, s32 arg1) {
    s32 sp10;

    D_800BA2BC = arg1;
    ((struct gd_18_f32 *)arg0)->v = D_80000E88;
    ((struct gd_10_s16 *)arg0)->v = D_80057F52[arg1].m0;
    ((struct gd_12_s16 *)arg0)->v = D_80057F52[arg1].m4;
    ((struct gd_14_s16 *)arg0)->v = D_80057F52[arg1].m8;
    ((struct gd_28_f32 *)arg0)->v = D_80057F5C[arg1].m0;
    ((struct gd_2C_f32 *)arg0)->v = D_80057F5C[arg1].m4;
    ((struct gd_30_f32 *)arg0)->v = D_80057F5C[arg1].m8;
    ((struct gd_48_s32 *)arg0)->v = 0;
    sp10 = func_8000A990(0x3010000, -1);
    if (sp10 != 0) {
        func_8000A4A4(sp10, 0);
    }
    if (D_80057F5C[arg1].mC != 0) {
        sp10 = func_8000A56C(((s32)&func_80016734), 0x3010000);
        ((struct gd_8_s32 *)((struct gd_30_s32 *)sp10)->v)->v = D_80057F5C[arg1].mC;
        ((struct gd_C_s32 *)((struct gd_30_s32 *)sp10)->v)->v = 0;
        ((struct gd_10_s32 *)((struct gd_30_s32 *)sp10)->v)->v = D_80057F5C[arg1].m10;
        D_800B6BE8 = D_80057F5C[arg1].m0;
        D_800B6BEC = D_80057F5C[arg1].m4;
        D_800B6BF0 = D_80057F5C[arg1].m8;
        return;
    }
    D_800BA5D8 = 0;
    D_800B6BE8 = 0;
    D_800B6BEC = 0;
    D_800B6BF0 = 0;
}
